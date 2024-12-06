#include <Nuntius/FileServer/ImageFileServer.hpp>
#include <stdexcept>

namespace nt::fileserver {

    ImageFileServer &ImageFileServer::read(const char *path, SDL_Surface &data) {
        SDL_Surface* surface = IMG_Load(path);
        if (!surface) {
            SDL_Log("[ERROR] Failed to load texture -> %s", SDL_GetError());
            return *this;
        }
        data = *surface;
        SDL_DestroySurface(surface);
        return *this;
    }

    ImageFileServer &ImageFileServer::write(const char *path, const SDL_Surface &data) {
        throw std::runtime_error("Not implemented");
        return *this;
    }
}