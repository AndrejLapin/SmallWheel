#pragma once

#include "SDL_events.h"

namespace swheel {
    class Event {
    public:
        Event() = default;

        SDL_Event* operator&() {
            m_handled = false;
            return &m_event;
        }

        bool m_handled = false;
        SDL_Event m_event;
    };
}
