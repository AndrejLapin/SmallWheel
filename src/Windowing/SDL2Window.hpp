#pragma once

#include "SDL_video.h"
#include <string>

namespace swheel {
    class SDL2Window {
    public:
        SDL2Window(const std::string& title, int width, int height);
        ~SDL2Window();

        void PollEvents();
        bool IsClosed() const { return m_closed; }

    private:
        bool Init();

    private:
        std::string m_title;
        int m_width;
        int m_height;

        bool m_closed = false;

        SDL_Window* m_window = nullptr;
        SDL_GLContext m_context = nullptr;
    };
}