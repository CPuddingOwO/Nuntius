#include <Nuntius/Game/World/WorldLoader.hpp>
#include <Nuntius/ObjectRegistry/ObjectRegistry.hpp>
#include <Nuntius/Game/World/Room.hpp>


#include <format>
#include <iostream>

namespace nt::world {
    void WorldLoader::uploadTileCollection(nlohmann::json &data) {
        auto m_world = ObjectRegistry::Get<World>();
        m_world->tiles = data["tiles"];
    }

    void WorldLoader::uploadMapData(nlohmann::json &data) {
        auto m_world = ObjectRegistry::Get<World>();
        auto m_room = ObjectRegistry::Get<Room>();
        m_world->fullWorld = data;

        std::cout << "[WorldLoader] Name->" << data["name"] << std::endl;
        for (auto& region : data["regions"]) {
            std::cout << "[WorldLoader]   Regions->" << region["name"] << std::endl;
            for (auto& subregion : region["subregions"]) {
                std::cout << "[WorldLoader]     Subregions->" << subregion["name"] << std::endl;
                for (auto& room : subregion["rooms"]) {
//                    std::cout << "[WorldLoader]       Room->" << room["name"] << std::endl;
                    if (room["isStartRoom"]) {
                        std::cout << "[WorldLoader]       Room->" << room["name"] << " ***" << std::endl;
                        m_world->setWorldByJson(data);

                        RoomInfo roomInfo;
                        roomInfo.roomID = std::format("{}.{}.{}.{}", data["name"].get<std::string>(), region["name"].get<std::string>(), subregion["name"].get<std::string>(), room["name"].get<std::string>());
                        m_room->setStartRoom(roomInfo);
                    }else{
                        std::cout << "[WorldLoader]       Room->" << room["name"] << std::endl;
                    }
                }
            }
        }
    }
}

