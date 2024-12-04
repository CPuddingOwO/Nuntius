#include <Nuntius/Game/Event/Events/LKeyPress.hpp>

namespace nt {
    LKeyPressEvent::LKeyPressEvent(int keyCode, bool isPressed)
            : keyCode(keyCode), isPressed(isPressed) {}

    EventType LKeyPressEvent::getType() const {
        return EventType::LKeyPress;
    }

    EventLevel LKeyPressEvent::getLevel() const {
        return EventLevel::Lower;
    }
}