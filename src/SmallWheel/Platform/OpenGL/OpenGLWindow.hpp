#pragma once

#include "OpenGLBackend.hpp"
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
        GraphicsBackend& GetGraphicsBackend() const override { return *m_backend.get();}

        int GetWidth() const { return m_width; }
        int GetHeight() const { return m_height; }
        SDL_Window* GetSDLWindow() const { return m_window; }
        SDL_GLContext GetSDLGLContext() const { return m_context; }
    private:
        void PushLayer(std::unique_ptr<Layer> layer) override;
        void PushOverlay(std::unique_ptr<Layer> overlay) override;
        bool Init();

    private:
        std::string m_title;
        int m_width;
        int m_height;

        std::unique_ptr<OpenGLBackend> m_backend;
        LayerStack m_layerStack;

        SDL_Window* m_window = nullptr;
        SDL_GLContext m_context = nullptr;

        bool m_closed = false;
    };
}
