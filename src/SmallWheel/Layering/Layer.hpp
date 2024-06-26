#pragma once

#include "SmallWheel/Event.hpp"
#include "SmallWheel/Window.hpp"

namespace  swheel {
    class Layer {
    public:
        Layer(const std::string& name = "Layer"): m_debugName(name) {}
        virtual ~Layer() {}

        virtual void OnAttach(const Window* window) {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnEvent(Event& event) {}

        inline const std::string& GetDebugName() const { return m_debugName; }
    protected:
        std::string m_debugName;
    };
}