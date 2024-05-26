#include "imgui.h"
#include "swpch.hpp"
#include "ImguiLayer.hpp"

#include "imgui/backends/imgui_impl_sdl2.h"

#include "SmallWheel/GraphicsBackend/GraphicsBackend.hpp"
#include "SmallWheel/GraphicsBackend/CommonVertexLayouts.hpp"
#include "SmallWheel/Platform/OpenGL/OpenGLWindow.hpp"
#include "SmallWheel/Platform/OpenGL/OpenGLImguiLayerImpl.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace swheel {
    ImguiLayer::ImguiLayer(const Window& owner, Application::SharedData& sharedData, const std::string& name): 
        Layer(owner, name),
        m_sharedData(sharedData) {
        RendererAPI apiType = owner.GetGraphicsBackend().GetAPIType();
        switch (apiType) {
        case RendererAPI::OpenGL: {
            m_layerImpl = std::make_unique<OpenGLImguiLayerImpl>(static_cast<const OpenGLWindow&>(owner));
        }break;
        }
    }

    ImguiLayer::~ImguiLayer() {

    }

    void ImguiLayer::OnAttach() {
        m_layerImpl->OnAttach();
    }

    void ImguiLayer::OnDetach() {
        m_layerImpl->OnDetach();
    }

    void ImguiLayer::OnUpdate() {
        m_layerImpl->ImguiFrameBegin();

        static std::vector<std::string> labels = {
            "vertex 0 pos",
            "vertex 1 pos",
            "vertex 2 pos"
        };

        static std::vector<std::string> colorLabels = {
            "vertex 0 col",
            "vertex 1 col",
            "vertex 2 col"
        };

        if (ImGui::CollapsingHeader("Mesh editor:", true)) {
            if (m_sharedData.meshData) {
                {
                    VertexPropertyView<propertyUnion::Triple> vertexPositions =
                        commonLayouts::PositionColor::GetPosition(*m_sharedData.meshData);
                    uint32_t currentVertexindex = 0;
                    for (auto& vertexPosition : vertexPositions) {
                        // std::string label("vertex " + std::to_string(currentVertexindex) + " position");
                        ImGui::SliderFloat3(labels[currentVertexindex].c_str(), &vertexPosition.x, -2.0, 2.0);
                        ++currentVertexindex;
                    }
                }

                {
                    uint32_t currentVertexindex = 0;
                    VertexPropertyView<propertyUnion::Quad> vertexColors =
                        commonLayouts::PositionColor::GetColor(*m_sharedData.meshData);
                    for (auto& vertexColor : vertexColors) {
                        ImGui::ColorEdit4(colorLabels[currentVertexindex].c_str(), &vertexColor.r);
                        ++currentVertexindex;
                    }
                }
            }
        }

        // static bool show = true;
        // ImGui::ShowDemoWindow(&show);

        m_layerImpl->ImguiFrameEnd();
    }

    void ImguiLayer::OnEvent(Event& event) {
        event.m_handled = ImGui_ImplSDL2_ProcessEvent(&event.m_event);
    }
}
