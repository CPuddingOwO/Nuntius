#pragma once
#include <Nuntius/Game/Event/EventType.hpp>

namespace nt {
    struct IEvent {
        virtual ~IEvent() = default;

        virtual EventType getType() const = 0;

        virtual EventLevel getLevel() const = 0;
    };
}