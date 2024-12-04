#pragma once

#include <Nuntius/Game/Event/IEventListener.hpp>
#include <Nuntius/API.hpp>
#include <cstdio>
#include <vector>

namespace nt {
    class NT_API EventDispatcher {
    public:
        void addListener(EventListener *listener);

        void removeListener(EventListener *listener);

        void dispatch(const IEvent &event);

    private:
        std::vector<EventListener *> listeners;
    };
}