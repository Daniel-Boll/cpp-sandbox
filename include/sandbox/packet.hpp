#pragma once

#include <cereal/archives/binary.hpp>

namespace network {

  enum class PacketType {
    CUSTOM_DATA,
    PLAYER_POSITION,
    // Add more packet types as needed
  };

  class BasePacket {
  public:
    virtual ~BasePacket() = default;
    virtual PacketType getType() const = 0;

    template <class Archive> void serialize(Archive& ar) {}
  };

  template <PacketType Type> class Packet : public BasePacket {
  public:
    PacketType getType() const override { return Type; }
  };

}  // namespace network
