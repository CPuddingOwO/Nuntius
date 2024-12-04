#include <Nuntius/Game/Flecs/FlecsWorld.hpp>
#include <Nuntius/Game/Flecs/FlecsComponents.hpp>
#include <Nuntius/Game/Flecs/FlecsSystems.hpp>
#include <iostream>

namespace nt::ecs {

    FlecsWorld::FlecsWorld() : world(flecs::world()) {

        RegistryComponent();
        RegistrySystem();

        auto e = world.entity("test")
                .set<Position>({0.0, 0.0, 0.0})
                .set<Velocity>({0.0, 2.0});
    }

    FlecsWorld::~FlecsWorld() {

    }

    void FlecsWorld::RegistryComponent() {
        world.component<Position>();
        world.component<Velocity>();
    }

    void FlecsWorld::RegistrySystem() {
        world.system<Position, Velocity>().each(MovementSystem);
        world.system<Velocity>().each(VelocitySystem);
    }
}