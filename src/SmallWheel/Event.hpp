#pragma once

#include "SDL_events.h"

namespace swheel {
    class Event {
    public:
        Event() = default;

        int PollNextEvent() {
            m_handled = false;
            return SDL_PollEvent(&m_event);
        }

        bool m_handled = false;
        SDL_Event m_event;
    };
}
