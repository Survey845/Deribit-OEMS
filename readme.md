# Deribit-OEMS

## An Order Execution and Mangement System for the Deribit Testnet using API

### Overview

Deribit-OEMS is an application written in C++ designed for interacting with the Test Deribit-API. It provides various functions like placing orders, viewing current positions and an additional functionality for clients to subscribe to specific tokens using websocket servers.

### This program allows you to;

- Place Orders
- Cancel Orders
- Modify Orders
- Get Order Book
- View Current Positions
- Websocket Servers
- Spot, futures and options for all supported symbols

### Ensure the following:

- You have installed all the files from the master branch
- After cloning the Deribit-OEMS repo, use the code provided below to use the websocketpp submodule:

  ```bash
  git submodule update --init --recursive
  ```

- Make sure you cURL library is updated
- Rename the .env.dist to .env and enter you API key and secret where it is mentioned. Keep in mind, do not put quotation marks around them, and leave no spaces.
