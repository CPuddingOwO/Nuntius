#include <Nuntius/Game/World/World.hpp>

namespace nt::world {

    void World::setWorldByJson(nlohmann::json &data) {
        full = data;
    }

    void World::setWorldMetaByJson(nlohmann::json &data) {
        meta = data;
    }

}