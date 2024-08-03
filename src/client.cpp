#include <print>
#include <sandbox/network.hpp>
#include <sandbox/player-position.hpp>
#include <thread>

int main() {
  network::NetworkManager client;

  if (!client.connectToServer("localhost", 12345)) {
    std::print("Failed to connect to server\n");
    throw std::runtime_error("Failed to connect to server");
  }

  std::print("Connected to server successfully");

  client.registerPacketHandler<network::PlayerPositionPacket>(
      [](const network::PlayerPositionPacket& packet, ENetPeer* sender) {
        std::print("Received player position: [{}, {}, {}]\nFrom: {}", packet.x, packet.y, packet.z,
                   sender->incomingPeerID);
      });

  std::srand(std::time(nullptr));

  while (true) {
    client.update();

    if (rand() % 100 < 1)
      client.sendToServer(
          network::PlayerPositionPacket{static_cast<float>(rand()) / RAND_MAX * 10.0f,
                                        static_cast<float>(rand()) / RAND_MAX * 10.0f,
                                        static_cast<float>(rand()) / RAND_MAX * 10.0f});

    std::this_thread::sleep_for(std::chrono::milliseconds(16));  // ~60 fps
  }

  return 0;
}
