#pragma once

#include "Renderer/Renderer.hpp"
#include "Layering/Layer.hpp"

namespace swheel {
    class Window {
    public:
        Window(const std::string& title, int width, int height): m_title(title), m_width(width), m_height(height) {}
        virtual ~Window() = default;

        virtual void OnEvent(Event& event) = 0;
        virtual void OnUpdate() = 0;
        virtual bool IsClosed() const = 0;

        virtual void PushLayer(std::unique_ptr<Layer> layer) = 0;
        virtual void PushOverlay(std::unique_ptr<Layer> layer) = 0;

        virtual Renderer& GetRenderer() = 0;

    protected:
        //maybe data should be moved to an actual class
        std::string m_title;
        int m_width;
        int m_height;
    };
}
