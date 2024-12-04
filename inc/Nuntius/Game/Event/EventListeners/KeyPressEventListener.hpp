#pragma once
#include <Nuntius/Game/Event/IEventListener.hpp>
#include <Nuntius/Game/Event/Events/LKeyPress.hpp>
#include <iostream>

namespace nt {
    class NT_API KeyPressListener : public EventListener {
    public:
        void onEvent(const IEvent &event) override;
    };
}