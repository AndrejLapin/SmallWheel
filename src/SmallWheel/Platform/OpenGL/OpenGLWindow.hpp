#pragma once

#include "OpenGLRenderer.hpp"
#include "SDL_video.h"
#include "SmallWheel/Layering/Layer.hpp"
#include "SmallWheel/Window.hpp"
#include "SmallWheel/Layering/LayerStack.hpp"

namespace swheel {
    class OpenGLWindow : public Window {
    public:
        OpenGLWindow(const std::string& title, int width, int height);
        ~OpenGLWindow() override;

        void OnEvent(Event& event) override;
        void OnUpdate() override;
        bool IsClosed() const override { return m_closed; }
        Renderer& GetRenderer() override { return *m_renderer.get();}

        void PushLayer(std::unique_ptr<Layer>) override;
        void PushOverlay(std::unique_ptr<Layer> layer) override;
    private:
        bool Init();

    private:
        std::unique_ptr<OpenGLRenderer> m_renderer;
        LayerStack m_layerStack;

        SDL_Window* m_window = nullptr;
        SDL_GLContext m_context = nullptr;

        bool m_closed = false;
    };
}
