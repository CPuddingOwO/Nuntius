#include <Nuntius/FileServer/JsonFileServer.hpp>
#include <iostream>

namespace nt::fileserver {

    JsonFileServer& JsonFileServer::read(const char *path, nlohmann::json &data) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Failed to open file for reading: " << path << std::endl;
            return *this;
        }
        data = nlohmann::json::parse(file);
        file.close();
        return *this;
    }

    JsonFileServer& JsonFileServer::write(const char *path, const nlohmann::json &data) {
        std::ofstream file(path);
        if (!file.is_open()) {
            std::cerr << "Failed to open file for writing: " << path << std::endl;
            return *this;
        }
        file << data;
        file.close();
        return *this;
    }
}