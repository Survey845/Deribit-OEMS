#pragma once
#include "../websocketpp/websocketpp/config/asio_no_tls.hpp"
#include "../websocketpp/websocketpp/server.hpp"
#include "json.hpp"
#include <set>
#include <mutex>
#include <string>

#pragma once

#include "../websocketpp/websocketpp/config/asio_no_tls.hpp"
#include "../websocketpp/websocketpp/server.hpp"
#include "json.hpp"
#include <set>
#include <mutex>
#include <string>

class WebSocketServer
{
public:
    using websocket_server_type = websocketpp::server<websocketpp::config::asio>;
    using connection_hdl = websocketpp::connection_hdl;

    WebSocketServer();
    void start_server();

private:
    websocket_server_type server;
    std::set<std::string> subscribers;
    std::mutex subscription_mutex;

    void on_message(connection_hdl hdl, websocket_server_type::message_ptr msg);
    void notifyClients(const nlohmann::json &orderbook_data);
    void order_book();
};
