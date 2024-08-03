#pragma once

#include <cereal/types/string.hpp>
#include <sandbox/packet.hpp>

namespace network {
  class CustomDataPacket : public Packet<PacketType::CUSTOM_DATA> {
  public:
    std::string data;

    template <class Archive> void serialize(Archive& ar) { ar(data); }
  };
}  // namespace network
