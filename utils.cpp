#include "include/utils.h"
#include <curl/curl.h>
#include <iostream>
#include "include/json.hpp"
#include "include/key_and_secret.h"

nlohmann::json Utility::authenticate()
{
    load_env();

    nlohmann::json payload_j = {
        {"jsonrpc", "2.0"},
        {"method", "public/auth"},
        {"params", {{"grant_type", "client_credentials"}, {"client_id", api_key}, {"client_secret", api_secret}, {"id", 1}}}

    };
    std::string payload = to_string(payload_j);
    // std::cout << payload << std::endl;
    // Post to authenticate
    std::string response = Utility::send_post("https://test.deribit.com/api/v2/public/auth", payload, "");
    auto json_response = nlohmann::json::parse(response);
    // std::cout << response << std::endl;
    if (json_response.contains("result") && json_response["result"].contains("access_token"))
    {
        std::string access_token = json_response["result"]["access_token"];
        // std::cout << "Access Token: " << access_token << std::endl;
        return access_token;
    }
    else
    {
        std::cerr << "Authentication failed. Response: " << response << std::endl;
        throw std::runtime_error("Authentication failed.");
    }
}

size_t Utility::write_callback(void *contents, size_t size, size_t nmemb, std::string *s)
{
    size_t newLength = size * nmemb;
    s->append((char *)contents, newLength);
    return newLength;
}

std::string Utility::send_post(const std::string &url, const std::string &payload, const std::string &auth_header)
{
    CURL *curl;
    CURLcode res;
    std::string read_buffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
        struct curl_slist *headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        if (!auth_header.empty())
        {
            headers = curl_slist_append(headers, auth_header.c_str());
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            std::cerr << "cURL Error: " << curl_easy_strerror(res) << std::endl;
        }
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return read_buffer;
}
