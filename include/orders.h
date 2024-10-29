#pragma once
#include <string>
#include "utils.h"

class OrderManager
{
private:
    std::string access_token = Utility::authenticate();

public:
    std::string buy_order(const std::string &symbol, double amount, double price);
    std::string sell_order(const std::string &symbol, double amount, double price);
    std::string cancel_order(const std::string &order_id);
    std::string modify_order(const std::string &order_id, double new_amount, double new_price);
    std::string get_orderbook(const std::string &symbol);
    std::string view_position();
};