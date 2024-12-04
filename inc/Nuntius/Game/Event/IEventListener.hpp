#pragma once

#include <Nuntius/Game/Event/IEvent.hpp>

namespace nt {
    class EventListener {
    public:
        virtual ~EventListener() = default;

        virtual void onEvent(const IEvent &event) = 0;
    };
}