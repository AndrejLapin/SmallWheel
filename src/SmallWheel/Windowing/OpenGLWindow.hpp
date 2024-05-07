#pragma once

#include "Window.hpp"
#include "SDL_video.h"

namespace swheel {
    class OpenGLWindow : public Window {
    public:
        OpenGLWindow(const std::string& title, int width, int height);
        ~OpenGLWindow() override;

        void OnEvent(Event& event) override;
        bool IsClosed() const override { return m_closed; }

    private:
        bool Init();

    private:
        bool m_closed = false;

        SDL_Window* m_window = nullptr;
        SDL_GLContext m_context = nullptr;
    };
}
