#pragma once
#include <Nuntius/API.hpp>
#include <flecs.h>
#include <Nuntius/Game/Flecs/FlecsComponents.hpp>

namespace nt::ecs {
    NT_API void MovementSystem(Position& pos, Velocity& vel);
    NT_API void VelocitySystem(Velocity& vel);
}
