#include <Nuntius/Game/World/Room.hpp>
#include <Nuntius/ObjectRegistry/ObjectRegistry.hpp>
#include <utility>
#include <Nuntius/StringEx.hpp>
#include "Nuntius/Game/World/World.hpp"

namespace nt::world {

    bool Room::findRoom(const RoomInfo& roomInfo) {
        auto world = ObjectRegistry::Get<World>();
        auto dst = split(roomInfo.roomID, '.');
//        auto r = world->fullWorld[dst[0]][dst[1]][dst[2]][dst[3]];
        if (world->fullWorld.contains(dst[0]) &&
            world->fullWorld[dst[0]].contains(dst[1]) &&
            world->fullWorld[dst[0]][dst[1]].contains(dst[2]) &&
            world->fullWorld[dst[0]][dst[1]][dst[2]].contains(dst[3])) {
            return true;
        }
        return false;
    }

    void Room::swapRoom(const RoomInfo& roomInfo) {
        rID = roomInfo.roomID;
        auto dst = split(roomInfo.roomID, '.');
        auto r = ObjectRegistry::Get<World>()->fullWorld[dst[0]][dst[1]][dst[2]][dst[3]];
        for (auto& tile : r["tiles"]) {
            TileInfo info;
            info.pos.x = tile["position"][0];
            info.pos.y = tile["position"][1];
            info.pos.z = tile["position"][2];
            auto t = Tile(info);
            roomTiles.push_back(t);
        }
    }

    void Room::setStartRoom(RoomInfo roomInfo) {
        room = std::move(roomInfo);
        swapRoom(room);
    }
}
