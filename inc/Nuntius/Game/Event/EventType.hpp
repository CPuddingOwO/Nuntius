#pragma once

namespace nt {
    enum class EventLevel {
        Lower,
        Middle,
        Upper
    };

    enum class EventType {
        LKeyPress,
        LMouseClick,
        UPlayerSpawn,
    };
}