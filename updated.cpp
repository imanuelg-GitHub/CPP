#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <fstream>
#include <map>
#include <regex>
#include <cstdlib>
#include <algorithm>

std::string hexify(const unsigned char* data, size_t len) {
    std::ostringstream ss;
    ss << std::hex << std::setfill('0');
    for (size_t i = 0; i < len; i++) ss << std::setw(2) << (int)data[i];
    return ss.str();
}

std::string hmac_sha256_raw(const std::string& key, const std::string& msg, unsigned int* out_len = nullptr) {
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int len = 0;
    HMAC(EVP_sha256(), key.data(), key.size(),
         reinterpret_cast<const unsigned char*>(msg.data()), msg.size(), hash, &len);
    if (out_len) *out_len = len;
    return std::string(reinterpret_cast<char*>(hash), len);
}

std::string sha256_hex(const std::string& msg) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(msg.data()), msg.size(), hash);
    return hexify(hash, SHA256_DIGEST_LENGTH);
}

std::string url_encode(const std::string& s) {
    std::ostringstream ss;
    ss << std::hex << std::uppercase;
    for (unsigned char c : s) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
            ss << c;
        else
            ss << '%' << std::setw(2) << std::setfill('0') << (int)c;
    }
    return ss.str();
}

std::map<std::string, std::string> load_aws_credentials(const std::string& profile = "default") {
    std::map<std::string, std::string> creds;
    const char* home = getenv("HOME");
    if (!home) return creds;
    std::ifstream file(std::string(home) + "/.aws/credentials");
    if (!file) return creds;
    std::string line, current;
    std::regex profile_re(R"(\[([^\]]+)\])");
    std::regex kv_re(R"(^\s*(\S+)\s*=\s*(.+?)\s*$)");
    while (std::getline(file, line)) {
        std::smatch m;
        if (std::regex_match(line, m, profile_re)) current = m[1];
        else if (current == profile && std::regex_match(line, m, kv_re)) creds[m[1]] = m[2];
    }
    return creds;
}

std::string generate_rds_auth_token(const std::string& hostname, int port,
                                    const std::string& region, const std::string& username,
                                    const std::string& access_key, const std::string& secret_key,
                                    const std::string& session_token = "",
                                    const std::string& amzdate_override = "",
                                    const std::string& datestamp_override = "") {

    time_t now = time(nullptr);
    struct tm tm; gmtime_r(&now, &tm);
    char date[9], amzdate[17];
    strftime(date, sizeof(date), "%Y%m%d", &tm);
    strftime(amzdate, sizeof(amzdate), "%Y%m%dT%H%M%SZ", &tm);
    std::string datestamp = datestamp_override.empty() ? date : datestamp_override;
    std::string amzdate_str = amzdate_override.empty() ? amzdate : amzdate_override;

    std::string credential_scope = datestamp + "/" + region + "/rds-db/aws4_request";

    std::map<std::string, std::string> query_params = {
        {"Action", "connect"},
        {"DBUser", username},
        {"X-Amz-Algorithm", "AWS4-HMAC-SHA256"},
        {"X-Amz-Credential", access_key + "/" + credential_scope},
        {"X-Amz-Date", amzdate_str},
        {"X-Amz-Expires", "900"},
        {"X-Amz-SignedHeaders", "host"}
    };
    if (!session_token.empty()) {
        query_params["X-Amz-Security-Token"] = session_token;
    }

    std::vector<std::pair<std::string, std::string>> sorted_params(query_params.begin(), query_params.end());
    std::sort(sorted_params.begin(), sorted_params.end());

    std::ostringstream query;
    for (const auto& kv : sorted_params) {
        query << url_encode(kv.first) << "=" << url_encode(kv.second) << "&";
    }
    std::string canonical_query = query.str();
    canonical_query.pop_back();

    std::ostringstream canonical_request;
    canonical_request << "GET\n/\n" << canonical_query << "\n"
                      << "host:" << hostname << "\n\n"
                      << "host\nUNSIGNED-PAYLOAD";

    std::string canonical_request_str = canonical_request.str();
    std::string canonical_request_hash = sha256_hex(canonical_request_str);

    std::ostringstream sts;
    sts << "AWS4-HMAC-SHA256\n" << amzdate_str << "\n"
        << credential_scope << "\n" << canonical_request_hash;

    std::string string_to_sign = sts.str();

    unsigned int sig_len = 0;
    std::string kDate = hmac_sha256_raw("AWS4" + secret_key, datestamp, &sig_len);
    std::string kRegion = hmac_sha256_raw(kDate, region, &sig_len);
    std::string kService = hmac_sha256_raw(kRegion, "rds-db", &sig_len);
    std::string kSigning = hmac_sha256_raw(kService, "aws4_request", &sig_len);
    std::string final_sig = hmac_sha256_raw(kSigning, string_to_sign, &sig_len);
    std::string signature = hexify(reinterpret_cast<const unsigned char*>(final_sig.data()), sig_len);

    std::cout << "\n--- CanonicalRequest ---\n" << canonical_request_str << "\n";
    std::cout << "\n--- StringToSign ---\n" << string_to_sign << "\n";
    std::cout << "\n--- Signature ---\n" << signature << "\n";

    return hostname + ":" + std::to_string(port) + "/?" + canonical_query + "&X-Amz-Signature=" + signature;
}

int main() {
    std::string profile = "default";
    auto creds = load_aws_credentials(profile);
    if (creds.empty()) {
        std::cerr << "Failed to load credentials from profile [" << profile << "]\n";
        return 1;
    }

    std::string host = "mydb.abc123.us-west-2.rds.amazonaws.com";
    int port = 5432;
    std::string region = "us-west-2";
    std::string user = "iamuser";

    std::string token = generate_rds_auth_token(
        host, port, region, user,
        creds["aws_access_key_id"],
        creds["aws_secret_access_key"],
        creds.count("aws_session_token") ? creds["aws_session_token"] : ""
    );

    std::cout << "\nRDS IAM Auth Token:\n" << token << std::endl;
    return 0;
}
