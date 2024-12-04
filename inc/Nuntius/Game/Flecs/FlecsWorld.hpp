#pragma once
#include <flecs.h>
#include <Nuntius/API.hpp>

namespace nt::ecs {
    class NT_API FlecsWorld final {
    public:
        flecs::world world;

        FlecsWorld();
        ~FlecsWorld();

    private:

        void RegistrySystem();
        void RegistryComponent();
    };
}