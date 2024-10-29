#include <iostream>
#include "include/server.h"
#include "include/orders.h"
#include "include/utils.h"

int main()
{
    OrderManager order_manager;

    // Buy order
    // std::string response = order_manager.buy_order("BTC-PERPETUAL", 10.0, 4000);

    // Sell order
    //  std::string response = order_manager.cancel_order("29233414007");

    // Get orderbook
    // std::string response = order_manager.get_orderbook("BTC-PERPETUAL");

    // View current positions
    // std::string response = order_manager.view_position();

    // Modify order
    // std::string response = order_manager.modify_order("29233457321", 20.0, 4000);

    // std::cout << "Order: " << response << std::endl;

    // Start Websocket
    WebSocketServer server;
    server.start_server();

    return 0;
}
