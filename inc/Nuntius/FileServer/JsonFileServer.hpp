#pragma once
#include <Nuntius/FileServer/IFileServer.hpp>
#include <fstream>
#include <nlohmann/json.hpp>

namespace nt::fileserver {
    class NT_API JsonFileServer : public IFileServer<nlohmann::json> {
    public:
        JsonFileServer& read(const char *path, nlohmann::json &data) override;
        JsonFileServer& write(const char *path, const nlohmann::json &data) override;
    };
}