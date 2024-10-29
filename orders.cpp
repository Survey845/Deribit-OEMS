#include "include/orders.h"
#include "include/utils.h"
#include "include/json.hpp"
#include <iostream>

// Function to place buy order
std::string OrderManager::buy_order(const std::string &symbol, double amount, double price)
{
    nlohmann::json payload_j = {
        {"jsonrpc", "2.0"},
        {"method", "private/buy"},
        {"params", {{"instrument_name", symbol}, {"amount", amount}, {"price", price}, {"type", "limit"}, {"direction", "buy"}}},
        {"id", 2}};

    std::string payload = to_string(payload_j);

    // Authorization header with the access token
    std::string auth_header = "Authorization: Bearer " + access_token;
    // std::cout << auth_header << std::endl;
    // POST with authorization header
    return Utility::send_post("https://test.deribit.com/api/v2/private/buy", payload, auth_header);
}

// Function to sell order
std::string OrderManager::sell_order(const std::string &symbol, double amount, double price)
{
    nlohmann::json payload_j = {
        {"jsonrpc", "2.0"},
        {"method", "private/sell"},
        {"params", {{"instrument_name", symbol}, {"amount", amount}, {"price", price}, {"type", "limit"}, {"direction", "sell"}}},
        {"id", 2}};

    std::string payload = to_string(payload_j);

    // Authorization header with the access token
    std::string auth_header = "Authorization: Bearer " + access_token;
    // std::cout << auth_header << std::endl;
    // POST with authorization header
    return Utility::send_post("https://test.deribit.com/api/v2/private/sell", payload, auth_header);
}

// Function to cancel order
std::string OrderManager::cancel_order(const std::string &order_id)
{
    nlohmann::json payload_j = {
        {"jsonrpc", "2.0"},
        {"method", "private/cancel"},
        {"params", {{"order_id", order_id}}},
        {"id", 2}};
    std::string payload = to_string(payload_j);
    std::string auth_header = "Authorization: Bearer " + access_token;
    std::cout << auth_header << std::endl;
    return Utility::send_post("https://test.deribit.com/api/v2/private/cancel", payload, auth_header);
}

// Function to modify order
std::string OrderManager::modify_order(const std::string &order_id, double new_amount, double new_price)
{
    nlohmann::json payload_j = {
        {"jsonrpc", "2.0"},
        {"method", "private/edit"},
        {"params", {{"order_id", order_id}, {"amount", new_amount}, {"price", new_price}}},
        {"id", 3},
        {"token", access_token}};
    std::string payload = to_string(payload_j);
    std::string auth_header = "Authorization: Bearer " + access_token;
    return Utility::send_post("https://test.deribit.com/api/v2/private/edit", payload, auth_header);
}

// Function to get orderbook
std::string OrderManager::get_orderbook(const std::string &symbol)
{
    nlohmann::json payload_j = {
        {"jsonrpc", "2.0"},
        {"method", "public/get_order_book"},
        {"params", {{"instrument_name", symbol}}},
        {"id", 4}};
    std::string payload = to_string(payload_j);
    return Utility::send_post("https://test.deribit.com/api/v2/public/get_order_book", payload);
}

// Function to view current position
std::string OrderManager::view_position()
{
    nlohmann::json payload_j = {
        {"jsonrpc", "2.0"},
        {"method", "private/get_positions"},
        {"params", {
                       {"instrument_name", "BTC"},
                       {"kind", "future"},
                   }},
        {"id", 5},
        {"token", access_token}};
    std::string payload = to_string(payload_j);
    std::string auth_header = "Authorization: Bearer " + access_token;
    return Utility::send_post("https://test.deribit.com/api/v2/private/get_positions", payload, auth_header);
}
