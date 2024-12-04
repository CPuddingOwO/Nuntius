#pragma once

#include <Nuntius/API.hpp>
#include <Nuntius/Vecturm.hpp>

namespace nt::world {

    struct NT_API TileInfo {
        int tileID;
        int texID;
        nt::vec::vec3<int> pos;
    };

    struct NT_API Tile {
        explicit Tile(TileInfo _info);
        TileInfo info;
    };

}
