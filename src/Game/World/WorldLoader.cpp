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

    void WorldLoader::uploadWorld(nlohmann::json &data) {
        auto m_world = ObjectRegistry::Get<World>();
        m_world->setWorldByJson(data);
    }

    void WorldLoader::uploadWorldStruct(nlohmann::json &data) {
        auto m_world = ObjectRegistry::Get<World>();
        m_world->setWorldMetaByJson(data);

    }

    void WorldLoader::parserWorld(nlohmann::json &data) {

    }

    void WorldLoader::parserWorldStruct(nlohmann::json &data) {
        auto m_room = ObjectRegistry::Get<Room>();
        for (auto& region : data["regions"]) {
            std::cout << "[WorldLoader] Regions-> " << region["name"] << std::endl;
            for (auto& subregion : region["subregions"]) {
                std::cout << "[WorldLoader]   Subregions-> " << subregion["name"] << std::endl;
                for (auto& room : subregion["rooms"]) {
                    if (!room.contains("isStartRoom")) {
                        std::cout << "[WorldLoader]       Room-> " << room["name"] << std::endl;
                        continue;
                    }
                    if (room["isStartRoom"].get<bool>()) {
                        std::cout << "[WorldLoader]       Room-> " << room["name"] << " ***" << std::endl;
                        RoomInfo roomInfo;
                        roomInfo.roomID = std::format("{}.{}.{}.{}", data["name"].get<std::string>(), region["name"].get<std::string>(), subregion["name"].get<std::string>(), room["name"].get<std::string>());
                        m_room->setStartRoom(roomInfo);
                    }else{
                        std::cout << "[WorldLoader]     Room-> " << room["name"] << std::endl;
                    }
                }
            }
        }
    }

    void WorldLoader::load() {
        parserWorldStruct(ObjectRegistry::Get<World>()->meta);
    }
}

