#pragma once
#include <Nuntius/API.hpp>
#include <SDL3/SDL_render.h>

#include <string>

namespace nt::props {
    class WindowProperties {
    public:
        int width = 0;
        int height = 0;
        int x = 0;
        int y = 0;
        bool isBorderless = false;
        std::string title;
        SDL_Window *window = nullptr;
    };
}