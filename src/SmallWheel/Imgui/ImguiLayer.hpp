#pragma once

#include "SmallWheel/Layering/Layer.hpp"

namespace swheel {
    class ImguiLayerImpl;
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
        std::unique_ptr<ImguiLayerImpl> m_layerImpl;
    };
}
