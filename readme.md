# Deribit-OEMS

## An Order Execution and Mangement System for the Deribit Testnet using API

### Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Dependencies](#dependencies)

### Overview

Deribit-OEMS is an application written in C++ designed for interacting with the Test Deribit-API. It provides various functions like placing orders, viewing current positions and an additional functionality for clients to subscribe to specific tokens using websocket servers.

### Features

- **Place Orders**
- **Cancel Orders**
- **Modify Orders**
- **Get Order Book**
- **View Current Positions**
- **Websocket Servers**
- **Spot, futures and options for all supported symbols**

### Prerequisites

- C++ Compiler (C++ 17)
- IDE (for example VS Code)

### Installation

- Clone the Deribit-OEMS master branch to your local device.
- After cloning the Deribit-OEMS repo, use the code provided below to use the websocketpp submodule:

  ```bash
  git submodule update --init --recursive
  ```

- Update your cURL library
- Rename the .env.dist to .env and enter you API key and secret where it is mentioned. Keep in mind, do not put quotation marks around them, and leave no spaces.

### Dependencies

- [cURL](https://curl.se/) to make HTTP requests
- [websocketpp](https://github.com/zaphoyd/websocketpp/tree/1b11fd301531e6df35a6107c1e8665b1e77a2d8e) for server side functionality
- [nlohmann/json](https://github.com/nlohmann/json) for JSON parsing
- [cpp-dotenv](https://github.com/adeharo9/cpp-dotenv) To read .env file
