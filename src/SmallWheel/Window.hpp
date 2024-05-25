#pragma once

#include "Event.hpp"
#include "GraphicsBackend/GraphicsBackend.hpp"

namespace swheel {
    class Layer;

    class Window {
    public:
        virtual ~Window() = default;

        virtual void OnEvent(Event& event) = 0;
        virtual void OnUpdate() = 0;
        virtual bool IsClosed() const = 0;

        template<typename T, typename... Args>
        void PushLayer(Args&&... args) {
            PushLayer(std::move(std::make_unique<T>(*this, std::forward<Args>(args)...)));
        }

        template<typename T, typename... Args>
        void PushOverlay(Args&&... args) {
            PushOverlay(std::move(std::make_unique<T>(*this, std::forward<Args>(args)...)));
        }

        virtual const GraphicsBackend& GetGraphicsBackend() const = 0;

    private:
        virtual void PushLayer(std::unique_ptr<Layer> layer) = 0;
        virtual void PushOverlay(std::unique_ptr<Layer> layer) = 0;
    };
}
