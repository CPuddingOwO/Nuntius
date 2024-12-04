#pragma once
#include "Tile.hpp"
#include <Nuntius/API.hpp>

#include <string>
#include <vector>

namespace nt::world {
    struct NT_API RoomInfo {
        std::string roomID;
        int entrypointIndex;
    };

    class NT_API Room {
    public:
        void setStartRoom(RoomInfo roomInfo);
        bool findRoom(const RoomInfo& roomInfo);
        void swapRoom(const RoomInfo& roomInfo);

        std::string rID;
    private:
        RoomInfo room;
        std::vector<Tile> roomTiles;
    };
}