#include <Nuntius/Game/World/WorldLoader.hpp>
#include <Nuntius/ObjectRegistry/ObjectRegistry.hpp>

#include "Nuntius/Game/World/Room.hpp"

#include <Nuntius/FileServer/JsonFileServer.hpp>
#include <format>
#include <iostream>

namespace nt::world {
    void WorldLoader::loadWorld(const char* path) {
        auto m_world = ObjectRegistry::Get<World>();
        auto m_room = ObjectRegistry::Get<Room>();

        nt::fileserver::JsonFileServer fileServer;
        nlohmann::json world;
        fileServer.read(path, world);
        std::cout << "[WorldLoader] Name->" << world["name"] << std::endl;
        for (auto& region : world["regions"]) {
            std::cout << "[WorldLoader]   Regions->" << region["name"] << std::endl;
            for (auto& subregion : region["subregions"]) {
                std::cout << "[WorldLoader]     Subregions->" << subregion["name"] << std::endl;
                for (auto& room : subregion["rooms"]) {
//                    std::cout << "[WorldLoader]       Room->" << room["name"] << std::endl;
                    if (room["isStartRoom"]) {
                        std::cout << "[WorldLoader]       Room->" << room["name"] << " ***" << std::endl;
                        m_world->setWorldByJson(world);

                        RoomInfo roomInfo;
                        roomInfo.roomID = std::format("{}.{}.{}.{}", world["name"].get<std::string>(), region["name"].get<std::string>(), subregion["name"].get<std::string>(), room["name"].get<std::string>());
                        m_room->setStartRoom(roomInfo);
                    }else{
                        std::cout << "[WorldLoader]       Room->" << room["name"] << std::endl;
                    }
                }
            }
        }
    }

    void WorldLoader::saveWorld(const char *path) {
        // TODO: save Data
    }
}

