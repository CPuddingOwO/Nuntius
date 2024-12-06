#pragma once
#include <Nuntius/API.hpp>
#include <Nuntius/FileServer/IFileServer.hpp>
#include <Nuntius/Game/Resource/Types.hpp>

namespace nt::fileserver {
    class NT_API ImageFileServer : public IFileServer<SDL_Surface> {
    public:
        ImageFileServer& read(const char *path, SDL_Surface &data) override;
        ImageFileServer& write(const char *path, const SDL_Surface &data) override;

    };
}