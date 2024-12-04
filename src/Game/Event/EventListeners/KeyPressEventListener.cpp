#include <Nuntius/Game/Event/EventListeners/KeyPressEventListener.hpp>

namespace nt {
    void KeyPressListener::onEvent(const IEvent &event)  {
        if (event.getType() == EventType::LKeyPress) {
            const auto& keyEvent = dynamic_cast<const LKeyPressEvent&>(event);
//            std::cout << "Key " << keyEvent.keyCode << " pressed: " << (keyEvent.isPressed ? "Down" : "Up") << std::endl;
        }
    }
}