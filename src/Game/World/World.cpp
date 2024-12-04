#include <Nuntius/Game/World/World.hpp>

namespace nt::world {

    void World::setWorldByJson(nlohmann::json &data) {
        fullWorld = data;
    }

}