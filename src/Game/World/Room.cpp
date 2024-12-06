#include <Nuntius/Game/World/Room.hpp>
#include <Nuntius/ObjectRegistry/ObjectRegistry.hpp>
#include <utility>
#include <Nuntius/StringEx.hpp>
#include <iostream>
#include "Nuntius/Game/World/World.hpp"

namespace nt::world {

    bool Room::findRoom(const RoomInfo& roomInfo) {
        auto world = ObjectRegistry::Get<World>();
        auto dst = split(roomInfo.roomID, '.');
//        auto r = world->fullWorld[dst[0]][dst[1]][dst[2]][dst[3]];
        if (world->meta.contains(dst[0]) &&
            world->meta[dst[0]].contains(dst[1]) &&
            world->meta[dst[0]][dst[1]].contains(dst[2]) &&
            world->meta[dst[0]][dst[1]][dst[2]].contains(dst[3])) {
            return true;
        }
        return false;
    }

    void Room::swapRoom(const RoomInfo& roomInfo) {
        auto m_world = ObjectRegistry::Get<World>();
        rID = roomInfo.roomID;
        auto dst = split(roomInfo.roomID, '.');
        auto r = ObjectRegistry::Get<World>()->full[dst[1]][dst[2]][dst[3]];
        for (int z = 0; z < r["tiles"].size(); z++) {
            for (int y = 0; y < r["tiles"][z].size(); y++) {
                for (int x = 0; x < r["tiles"][z][y].size(); x++) {
                    auto tID = r["tiles"][z][y][x].get<int>();
//                    std::cout << "[WorldLoader] [" << tID << "]";
//                    std::cout << " -> " << x << ", " << y << ", " << z << std::endl;
                    TileInfo info{};
                    info.tileID = tID;
                    info.pos = {x, y, z};
                    info.texID = m_world->tiles[tID]["texID"].get<std::string>();
                    tailGrid.emplace_back(info);
                }
            }
        }
    }

    void Room::setStartRoom(RoomInfo roomInfo) {
        room = std::move(roomInfo);
        swapRoom(room);
    }
}
