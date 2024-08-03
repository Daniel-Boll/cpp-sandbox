#include <sandbox/network.hpp>

namespace network {
  NetworkManager::NetworkManager() {
    if (enet_initialize() != 0) {
      throw std::runtime_error("Failed to initialize ENet");
    }
  }

  NetworkManager::~NetworkManager() {
    disconnect();
    enet_deinitialize();
  }

  bool NetworkManager::createServer(uint16_t port, size_t maxClients) {
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = port;

    server = enet_host_create(&address, maxClients, 2, 0, 0);
    return server != nullptr;
  }

  bool NetworkManager::connectToServer(const char* hostName, uint16_t port) {
    client = enet_host_create(nullptr, 1, 2, 0, 0);
    if (!client) return false;

    ENetAddress address;
    enet_address_set_host(&address, hostName);
    address.port = port;

    serverPeer = enet_host_connect(client, &address, 2, 0);
    return serverPeer != nullptr;
  }

  void NetworkManager::disconnect() {
    if (serverPeer) {
      enet_peer_disconnect(serverPeer, 0);
      enet_host_flush(client);
      enet_peer_reset(serverPeer);
      serverPeer = nullptr;
    }
    if (client) {
      enet_host_destroy(client);
      client = nullptr;
    }
    if (server) {
      for (ENetPeer* peer : connectedPeers) {
        enet_peer_disconnect(peer, 0);
      }
      enet_host_flush(server);
      enet_host_destroy(server);
      server = nullptr;
    }
    connectedPeers.clear();
  }

  void NetworkManager::update() {
    ENetEvent event;
    ENetHost* activeHost = server ? server : client;

    while (enet_host_service(activeHost, &event, 0) > 0) {
      switch (event.type) {
        case ENET_EVENT_TYPE_CONNECT: {
          std::print("Peer connected: {}\n", event.peer->incomingPeerID);
          if (isServer()) {
            addPeer(event.peer);
          }
          break;
        }
        case ENET_EVENT_TYPE_RECEIVE: {
          std::vector<uint8_t> data(event.packet->data,
                                    event.packet->data + event.packet->dataLength);
          handlePacket(data, event.peer);
          enet_packet_destroy(event.packet);
          break;
        }
        case ENET_EVENT_TYPE_DISCONNECT:
          if (isServer()) {
            removePeer(event.peer);
          }
          break;
        default:
          break;
      }
    }
  }

  void NetworkManager::handlePacket(const std::vector<uint8_t>& data, ENetPeer* peer) {
    std::istringstream iss(std::string(data.begin(), data.end()));
    cereal::BinaryInputArchive archive(iss);

    PacketType type;
    archive(type);

    auto it = packetHandlers.find(type);
    if (it != packetHandlers.end()) {
      it->second(data, peer);
    }
  }

  void NetworkManager::addPeer(ENetPeer* peer) { connectedPeers.insert(peer); }

  void NetworkManager::removePeer(ENetPeer* peer) { connectedPeers.erase(peer); }
}  // namespace network
