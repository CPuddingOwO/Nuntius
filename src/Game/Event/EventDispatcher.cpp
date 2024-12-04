#include <Nuntius/Game/Event/EventDispatcher.hpp>

namespace nt {

    void EventDispatcher::addListener(EventListener *listener)  {
        listeners.push_back(listener);
    }

    void EventDispatcher::removeListener(EventListener *listener)   {
        listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
    }

    void EventDispatcher::dispatch(const IEvent &event) {
        for (auto &listener: listeners) {
            listener->onEvent(event);
        }
    }

}

