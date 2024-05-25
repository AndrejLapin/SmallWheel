#include "swpch.hpp"
#include "ImguiLayer.hpp"

#include "imgui/backends/imgui_impl_sdl2.h"

#include "SmallWheel/GraphicsBackend/GraphicsBackend.hpp"
#include "SmallWheel/Platform/OpenGL/OpenGLWindow.hpp"
#include "SmallWheel/Platform/OpenGL/OpenGLImguiLayerImpl.hpp"

namespace swheel {
    ImguiLayer::ImguiLayer(const Window& owner, const std::string& name): 
        Layer(owner, name) {
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

        m_layerImpl->OnUpdate();

        m_layerImpl->ImguiFrameEnd();
    }

    void ImguiLayer::OnEvent(Event& event) {
        event.m_handled = ImGui_ImplSDL2_ProcessEvent(&event.m_event);
    }
}
