#pragma once

#include "SmallWheel/Event.hpp"
#include "SmallWheel/Window.hpp"

namespace  swheel {
    class Layer {
    public:
        Layer(Window& owner, const std::string& name = "Layer"): m_ownerWindow(owner), m_debugName(name) {}
        virtual ~Layer() {}

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnEvent(Event& event) {}

        inline const std::string& GetDebugName() const { return m_debugName; }
    protected:
        Window& m_ownerWindow;
        std::string m_debugName;
    };
}