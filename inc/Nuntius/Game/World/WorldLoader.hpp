#pragma once
#include <Nuntius/Game/World/World.hpp>
#include "Room.hpp"

#include <Nuntius/API.hpp>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>

namespace nt::world {
    class NT_API WorldLoader {
    public:
        void uploadWorldStruct(nlohmann::json& data);
        void uploadWorld(nlohmann::json& data);
        void uploadTileCollection(nlohmann::json& data);
        void load();
    private:
        void parserWorld(nlohmann::json& data);
        void parserWorldStruct(nlohmann::json& data);

        std::vector<World> worlds;
    };
}