#pragma once

#include "Layer.hpp"
#include <cstdint>

namespace swheel {
    class OpenGLWindow;

    class ImguiLayer : public Layer {
    public:
        ImguiLayer(const Window& owner, const std::string& name = "Layer");
        ~ImguiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event& event) override;

    private:
        void ImguiFrameBegin();
        void ImguiFrameEnd();

        const OpenGLWindow& m_ownerOpenGLWindow;
    };
}
