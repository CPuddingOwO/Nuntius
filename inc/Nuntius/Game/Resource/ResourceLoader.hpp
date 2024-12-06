#pragma once
#include <Nuntius/API.hpp>
#include <Nuntius/Game/Resource/Types.hpp>

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace nt::res {
    class NT_API ResourceLoader {
    public:
        template<typename T>
        void Add(const types::ResourceInfo& info) {
            std::shared_ptr<T> resource = std::make_shared<T>();
            resource.load(info.path);
            resources.emplace(info.id, resource);
        }

        template<typename T>
        void Add(const std::string& id, const std::string& path) {
            std::shared_ptr<T> resource = std::make_shared<T>();
            resource->load(path);
            resources.emplace(id, resource);
        }

        std::shared_ptr<types::Resource> Get(const std::string& id) {
            auto it = resources.find(id); // ERROR
            if (it != resources.end()) {
                return it->second;
            }
            return nullptr;
        }

    private:
        std::unordered_map<std::string, std::shared_ptr<types::Resource>> resources = {};
    };
}