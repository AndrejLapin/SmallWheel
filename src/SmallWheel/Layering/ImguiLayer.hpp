#pragma once

#include "Layer.hpp"
#include <cstdint>

namespace swheel {
    class OpenGLWindow;

    class ImguiLayer : public Layer {
    public:
        ImguiLayer(Window& owner, const std::string& name = "Layer");
        ~ImguiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
    private:
        OpenGLWindow* m_ownerOpenGLWindow;
        uint32_t m_time = 0.0f;
    };
}
