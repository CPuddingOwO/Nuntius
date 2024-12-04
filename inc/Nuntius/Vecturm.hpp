#pragma once

#include <Nuntius/API.hpp>

namespace nt::vec {
    template<typename T = double>
    struct NT_API vec2 final {
        T x, y;
    };

    template<typename T = double>
    struct NT_API vec3 final {
        T x, y, z;
    };

    template<typename T = double>
    struct NT_API vec4 final {
        T x, y, z, w;
    };

    struct NT_API color final {
        int r, g, b, a;
    };
}