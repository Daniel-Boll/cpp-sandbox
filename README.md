# Networked Game Architecture

## Overview

This project demonstrates a basic networked game architecture using C++, ENet for networking, and Cereal for serialization. The goal is to create a flexible, extensible system for multiplayer game development that allows easy implementation of various packet types and efficient communication between clients and a central server.

## Key Components

### NetworkManager

The core of the system is the `NetworkManager` class, which handles both server and client functionalities. It provides methods for:

- Creating a server
- Connecting to a server
- Sending packets
- Broadcasting packets
- Registering packet handlers

### Packet System

The packet system is designed to be easily extensible:

- `BasePacket`: The base class for all packet types.
- `Packet<Type>`: A template class that derives from `BasePacket`, used to create specific packet types.
- Custom packet types (e.g., `PlayerPositionPacket`): Derive from `Packet<Type>` and implement their own serialization logic.

### Serialization

Cereal is used for serialization, allowing easy conversion of C++ objects to binary data for network transmission.

## Key Features

1. **Type-Safe Packet Handling**: Packet handlers are registered with specific packet types, ensuring type safety.
2. **Automatic Serialization**: Packets are automatically serialized and deserialized using Cereal.
3. **Flexible Broadcasting**: The server can broadcast messages to all clients or to all clients except the sender.
4. **Separation of Client and Server**: The architecture supports separate client and server applications.

## Example: Player Position Updates

The example implementation demonstrates a simple use case:

1. Clients periodically send their position to the server.
2. The server receives these updates and broadcasts them to all other connected clients.
3. Clients receive position updates from other players and can update their local game state accordingly.

## Project Structure

- `network_manager.hpp/cpp`: Core networking functionality.
- `packet_types.hpp`: Definitions for packet types and base classes.
- `player_position_packet.hpp`: Example of a custom packet type.
- `server.cpp`: Server application.
- `client.cpp`: Client application.

## Usage

1. Compile the server and client applications separately.
2. Run the server on a host machine.
3. Run multiple client instances, which will connect to the server.
4. Clients will send simulated position updates, and the server will relay these to other clients.

## Extensibility

To add new types of game events or data:

1. Create a new packet type deriving from `Packet<Type>`.
2. Implement the serialization logic for the new packet type.
3. Register handlers for the new packet type in both client and server applications.

This architecture provides a foundation for building more complex networked game systems, allowing for easy addition of new features and game-specific logic.
