#include <print>
#include <sandbox/network.hpp>
#include <sandbox/player-position.hpp>
#include <thread>

int main() {
  network::NetworkManager server;

  if (!server.createServer(12345, 32)) {
    std::print("Failed to create server\n");
    throw std::runtime_error("Failed to create server");
  }

  std::print("Server created successfully\n");

  server.registerPacketHandler<network::PlayerPositionPacket>(
      [&server](const network::PlayerPositionPacket& packet, ENetPeer* sender) {
        std::print("[{}] player position: [{}, {}, {}]\n", sender->incomingPeerID, packet.x,
                   packet.y, packet.z);

        server.broadcastToOthers(packet, sender);
      });

  while (true) {
    server.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(16));  // ~60 fps
  }

  return 0;
}
