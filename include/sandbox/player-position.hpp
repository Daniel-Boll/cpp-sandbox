#pragma once

#include <sandbox/packet.hpp>

namespace network {

  class PlayerPositionPacket : public Packet<PacketType::PLAYER_POSITION> {
  public:
    float x, y, z;

    PlayerPositionPacket(float x, float y, float z) : x(x), y(y), z(z) {}

    template <class Archive> void serialize(Archive& ar) { ar(x, y, z); }
  };

}  // namespace network
