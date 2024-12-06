#include <Nuntius/Game/Resource/Types.hpp>
#include <Nuntius/FileServer/ImageFileServer.hpp>
#include <Nuntius/ObjectRegistry/ObjectRegistry.hpp>
#include <Nuntius/Game/Props/RendererProperties.hpp>

namespace nt::types {
    bool Texture::load(const std::string& path) {
        auto renderer = ObjectRegistry::Get<props::RendererProperties>()->renderer;
        fileserver::ImageFileServer server;
        SDL_Surface surface;
        server.read(path.c_str(), surface);
        w = surface.w;
        h = surface.h;
        SDL_PropertiesID props = SDL_CreateProperties();
        SDL_SetNumberProperty(props, SDL_PROP_TEXTURE_CREATE_FORMAT_NUMBER, surface.format);
        SDL_SetNumberProperty(props, SDL_PROP_TEXTURE_CREATE_ACCESS_NUMBER, SDL_TEXTUREACCESS_STATIC);
        SDL_SetNumberProperty(props, SDL_PROP_TEXTURE_CREATE_WIDTH_NUMBER, w);
        SDL_SetNumberProperty(props, SDL_PROP_TEXTURE_CREATE_HEIGHT_NUMBER, h);
        texture = SDL_CreateTextureWithProperties(renderer, props);
//        texture = SDL_CreateTextureFromSurface(renderer, &surface);
        if (!texture) {
            SDL_Log("Error creating texture from surface: %s", SDL_GetError());
            return false;
        }
//        SDL_DestroySurface(&surface);
        return true;
    }

    bool Sound::load(const std::string& path) { return true; }
}