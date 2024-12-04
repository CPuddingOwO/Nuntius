// LKeyPressEvent.hpp
#pragma once
#include <Nuntius/API.hpp>
#include <Nuntius/Game/Event/IEvent.hpp>

namespace nt {
    struct NT_API LKeyPressEvent : public IEvent {
        int keyCode;
        bool isPressed;

        LKeyPressEvent(int keyCode, bool isPressed);

        EventType getType() const override;

        EventLevel getLevel() const override;
    };
}