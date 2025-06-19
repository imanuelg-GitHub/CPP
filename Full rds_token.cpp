#include <openssl/hmac.h>
#include <openssl/evp.h>
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

// --- Utility Functions ---

std::string hexify(const unsigned char* data, int len) {
    std::ostringstream ss;
    ss << std::hex << std::setfill('0');
    for (int i = 0; i < len; i++) ss << std::setw(2) << (int)data[i];
    return ss.str();
}

std::string hmac_sha256(const std::string& key, const std::string& msg) {
    unsigned char hash[EVP_MAX_MD_SIZE]; unsigned int len = 0;
    HMAC(EVP_sha256(), key.data(), key.size(),
         reinterpret_cast<const unsigned char*>(msg.data()), msg.size(), hash, &len);
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
            ss << '%' << std::setw(2) << std::setfill('0') << int(c);
    }
    return ss.str();
}

// --- INI Credential Loader from ~/.aws/credentials ---

std::map<std::string, std::string> load_aws_credentials(const std::string& profile = "adfs") {
    std::map<std::string, std::string> creds;

    const char* home = getenv("HOME");
    if (!home) {
        std::cerr << "HOME environment variable not set.\n";
        return creds;
    }

    std::string path = std::string(home) + "/.aws/credentials";
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Cannot open AWS credentials file at " << path << "\n";
        return creds;
    }

    std::string line, current_profile;
    std::regex profile_re(R"(\[([^\]]+)\])");
    std::regex kv_re(R"(^\s*(\S+)\s*=\s*(.+?)\s*$)");

    while (std::getline(file, line)) {
        std::smatch match;
        if (std::regex_match(line, match, profile_re)) {
            current_profile = match[1];
        } else if (current_profile == profile && std::regex_match(line, match, kv_re)) {
            creds[match[1]] = match[2];
        }
    }

    return creds;
}

// --- Core Auth Token Generator ---

std::string generate_rds_auth_token(
    const std::string& hostname, int port,
    const std::string& region, const std::string& username,
    const std::string& access_key, const std::string& secret_key,
    const std::string& session_token = "") {

    time_t now = time(nullptr);
    struct tm tm; gmtime_r(&now, &tm);
    char date[9], amzdate[17];
    strftime(date, sizeof(date), "%Y%m%d", &tm);
    strftime(amzdate, sizeof(amzdate), "%Y%m%dT%H%M%SZ", &tm);
    std::string credential_scope = std::string(date) + "/" + region + "/rds-db/aws4_request";

    std::ostringstream canonical_query;
    canonical_query << "Action=connect"
                    << "&DBUser=" << url_encode(username)
                    << "&X-Amz-Algorithm=AWS4-HMAC-SHA256"
                    << "&X-Amz-Credential=" << url_encode(access_key + "/" + credential_scope)
                    << "&X-Amz-Date=" << amzdate
                    << "&X-Amz-Expires=900"
                    << "&X-Amz-SignedHeaders=host";
    if (!session_token.empty()) {
        canonical_query << "&X-Amz-Security-Token=" << url_encode(session_token);
    }

    std::string canonical_query_str = canonical_query.str();

    std::ostringstream canonical_request;
    canonical_request << "GET\n"
                      << "/\n"
                      << canonical_query_str << "\n"
                      << "host:" << hostname << "\n\n"
                      << "host\n"
                      << "UNSIGNED-PAYLOAD";
    std::string hashed_canonical_request = sha256_hex(canonical_request.str());

    std::ostringstream string_to_sign;
    string_to_sign << "AWS4-HMAC-SHA256\n"
                   << amzdate << "\n"
                   << credential_scope << "\n"
                   << hashed_canonical_request;

    std::string kDate = hmac_sha256("AWS4" + secret_key, date);
    std::string kRegion = hmac_sha256(kDate, region);
    std::string kService = hmac_sha256(kRegion, "rds-db");
    std::string kSigning = hmac_sha256(kService, "aws4_request");

    std::string raw_sig = hmac_sha256(kSigning, string_to_sign.str());
    std::string signature = hexify(reinterpret_cast<const unsigned char*>(raw_sig.data()), raw_sig.size());

    std::ostringstream token;
    token << hostname << ":" << port << "/?" << canonical_query_str
          << "&X-Amz-Signature=" << signature;

    return token.str();
}

// --- Main ---

int main() {
    std::string profile = "adfs";
    auto creds = load_aws_credentials(profile);

    if (creds.empty()) {
        std::cerr << "Failed to load AWS credentials from profile [" << profile << "]\n";
        return 1;
    }

    std::string hostname = "mydb.abc123.us-west-2.rds.amazonaws.com";
    int port = 5432;
    std::string region = "us-west-2";
    std::string username = "iamuser";

    std::string access_key = creds["aws_access_key_id"];
    std::string secret_key = creds["aws_secret_access_key"];
    std::string session_token = creds.count("aws_session_token") ? creds["aws_session_token"] : "";

    std::string token = generate_rds_auth_token(
        hostname, port, region, username, access_key, secret_key, session_token);

    std::cout << "\nRDS Auth Token:\n" << token << "\n";
    return 0;
}


g++ -std=c++11 -o rds_token rds_token.cpp -lssl -lcrypto
