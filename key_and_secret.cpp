#include <iostream>
#include "include/dotenv.h" // Use a dotenv library header

std::string api_key;
std::string api_secret;

void load_env()
{
    dotenv env(0, NULL, false, ".env");
    api_key = env["API_KEY"];
    api_secret = env["API_SECRET"];
}