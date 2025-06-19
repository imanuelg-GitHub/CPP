#include <aws/core/Aws.h>
#include <aws/core/auth/AWSCredentials.h>
#include <aws/core/client/ClientConfiguration.h>
#include <aws/rds/RDSClient.h>
#include <iostream>

int main() {
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        // ----- Input Values -----
        Aws::String access_key = "AKIAEXAMPLE123456";
        Aws::String secret_key = "wJalrXUtnFEMI/K7MDENG+bPxRfiCYEXAMPLEKEY";
        Aws::String session_token = "IQoJb3JpZ2luX2Vj..."; // optional
        Aws::String region = "us-west-2";
        Aws::String hostname = "mydb.abc123.us-west-2.rds.amazonaws.com";
        int port = 5432;
        Aws::String username = "iamuser";

        // ----- Credentials & Config -----
        Aws::Auth::AWSCredentials credentials(access_key, secret_key, session_token);

        Aws::Client::ClientConfiguration config;
        config.region = region;

        Aws::RDS::RDSClient rdsClient(credentials, config);

        // ----- Generate Auth Token -----
        Aws::String authToken = rdsClient.GenerateConnectAuthToken(
            hostname, region, port, username);

        std::cout << "Generated RDS IAM Auth Token:\n" << authToken << std::endl;
    }
    Aws::ShutdownAPI(options);
    return 0;
}
