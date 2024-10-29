#include "websocketpp/websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/websocketpp/server.hpp"
#include <iostream>
#include <mutex>
#include "include/json.hpp"
#include <thread>
#include <chrono>
#include "include/server.h" // Assuming all required functions are declared here

WebSocketServer::WebSocketServer()
{
    server.init_asio();
}

// Message handler for incoming messages
void WebSocketServer::on_message(connection_hdl hdl, websocket_server_type::message_ptr msg)
{
    nlohmann::json message = nlohmann::json::parse(msg->get_payload());

    if (message.contains("subscribe"))
    {
        std::string symbol = message["subscribe"];
        std::lock_guard<std::mutex> lock(subscription_mutex);
        subscribers.insert(symbol);
        std::cout << "Client subscribed to: " << symbol << std::endl;
    }
    else if (message.contains("unsubscribe"))
    {
        std::string symbol = message["unsubscribe"];
        std::lock_guard<std::mutex> lock(subscription_mutex);
        subscribers.erase(symbol);
        std::cout << "Client unsubscribed from: " << symbol << std::endl;
    }
}

// Notify subscribed clients with order book updates
void WebSocketServer::notifyClients(const nlohmann::json &orderbook_data)
{
    std::lock_guard<std::mutex> lock(subscription_mutex);
    for (const std::string &symbol : subscribers)
    {
        if (orderbook_data.contains(symbol))
        {
            std::cout << "Notifying clients about updates for: " << symbol << std::endl;
            std::cout << orderbook_data.at(symbol).dump(4) << std::endl;
        }
    }
}

// Simulated continuous order book update loop
void WebSocketServer::order_book()
{
    while (true)
    {
        nlohmann::json orderbook_data;
        // Populate `orderbook_data` with actual or dummy data
        orderbook_data["BTCUSD"] = {{"price", 10000}, {"volume", 5}};
        orderbook_data["ETHUSD"] = {{"price", 3000}, {"volume", 10}};

        notifyClients(orderbook_data);                          // Send updates to subscribed clients
        std::this_thread::sleep_for(std::chrono::seconds(600)); // Adjust frequency as needed
    }
}

// Start the WebSocket server
void WebSocketServer::start_server()
{
    server.set_message_handler(std::bind(&WebSocketServer::on_message, this, std::placeholders::_1, std::placeholders::_2));
    server.listen(9002);   // Listen on port 9002
    server.start_accept(); // Start accepting connections

    std::cout << "Server started on ws://localhost:9002" << std::endl;

    // Create a thread to run the order book updates
    std::thread orderbook_thread(&WebSocketServer::order_book, this); // Pass `this` to bind the instance
    server.run();                                                     // Start the server loop
    orderbook_thread.join();                                          // Wait for the order book thread to finish
}
