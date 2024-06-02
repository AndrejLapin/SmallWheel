#pragma once

#include "SmallWheel/Layering/Layer.hpp"
#include "SmallWheel/Application.hpp"

namespace swheel {
    class ImguiLayerImpl;
    class OpenGLWindow;

    class ImguiLayer : public Layer {
    public:
        ImguiLayer(Application::SharedData& sharedData, const std::string& name = "Layer");
        ~ImguiLayer();

        void OnAttach(const Window* window) override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event& event) override;

    private:
        Application::SharedData& m_sharedData;
        std::unique_ptr<ImguiLayerImpl> m_layerImpl;
    };
}
