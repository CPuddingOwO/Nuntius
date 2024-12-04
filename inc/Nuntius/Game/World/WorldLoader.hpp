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
        void loadWorld(const char* path);
        void saveWorld(const char* path);
        void loadRoom();
    private:
        std::vector<World> worlds;
    };
}