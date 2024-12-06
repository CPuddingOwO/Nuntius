#pragma once
#include <Nuntius/API.hpp>

#include <vector>
#include <nlohmann/json.hpp>

namespace nt::world {
    class NT_API World {
    public:
        void setWorldByJson(nlohmann::json& data);
        void setWorldMetaByJson(nlohmann::json& data);
        nlohmann::json full;
        nlohmann::json meta;
        nlohmann::json tiles;
    };
}