#pragma once

#include "Event.hpp"
#include "Utils/RefCounted.hpp"
#include "GraphicsBackend/GraphicsBackend.hpp"

namespace swheel {
    class Layer;

    class Window {
    public:
        Window(const GraphicsBackend& parentBackend): m_parentBackend(parentBackend) {}
        virtual ~Window() = default;

        virtual void OnEvent(Event& event) = 0;
        virtual void OnUpdate() = 0;
        virtual bool IsClosed() const = 0;

        virtual void PushLayer(RefCounted<Layer> layer) = 0;
        virtual void PushOverlay(RefCounted<Layer> layer) = 0;

        const GraphicsBackend& GetGraphicsBackend() const { return m_parentBackend; }

    private:
        const GraphicsBackend& m_parentBackend;
    };
}
