#pragma once

#include <string>
#include <iostream>
#include <curl/curl.h>
#include "json.hpp"

namespace Utility
{

    // Functions
    std::string send_post(const std::string &url, const std::string &body, const std::string &auth_header = "");
    nlohmann::json authenticate();

    // Callback
    static size_t write_callback(void *contents, size_t size, size_t nmemb, std::string *s);
}