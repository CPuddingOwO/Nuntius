#include <Nuntius/Game/Flecs/FlecsSystems.hpp>

namespace nt::ecs {

    void MovementSystem(Position& pos, Velocity& vel) {
        pos.x += vel.x;
        pos.y += vel.y;
    }

    void VelocitySystem(Velocity& vel) {
        double friction = 0.99;
        if (vel.x < 0.0001) vel.x += friction; else vel.x = 0;
        if (vel.y < 0.0001) vel.y += friction; else vel.y = 0;
        vel.x *= friction;
        vel.y *= friction;
    }

}