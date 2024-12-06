#pragma once

#include <Nuntius/API.hpp>
#include <string>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_image/SDL_image.h>

namespace nt::types {

    enum class ResourceType {
        eInvalid,
        eTexture,
        eSound
    };

    class NT_API ResourceInfo{
    public:
        ResourceType type{};
        std::string id;
        std::string path;
    };

    class NT_API Resource {
    public:
        virtual ~Resource() = default;
        virtual bool load(const std::string& path) = 0;
    };
    class NT_API Texture : public Resource {
    public:
        SDL_Texture* texture = nullptr;
        bool load(const std::string& path) override;
    };

    class NT_API Sound : public Resource {
    public:
        Mix_Chunk* sound = nullptr;
        ~Sound() override {
            if (sound) Mix_FreeChunk(sound);
        };
        bool load(const std::string& path) override;
    };
}