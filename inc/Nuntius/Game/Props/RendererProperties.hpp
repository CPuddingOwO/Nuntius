#pragma once
#include <Nuntius/API.hpp>
#include <SDL3/SDL_render.h>

namespace nt::props {
    class RendererProperties {
    public:
        SDL_Renderer *renderer = nullptr;
        bool isVsync = false;
    };
}