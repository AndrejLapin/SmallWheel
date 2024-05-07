#pragma once

#include "Window.hpp"
#include "SDL_video.h"
#include "SmallWheel/Layering/LayerStack.hpp"

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
        LayerStack m_layerStack;

        SDL_Window* m_window = nullptr;
        SDL_GLContext m_context = nullptr;

        bool m_closed = false;
    };
}
