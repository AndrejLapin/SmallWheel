#include "swpch.hpp"
#include "OpenGLImguiLayerImpl.hpp"

#include "imgui.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/backends/imgui_impl_opengl3.h"

namespace swheel {
    OpenGLImguiLayerImpl::OpenGLImguiLayerImpl(const OpenGLWindow& ownerWindow): m_ownerWindow(ownerWindow) {}

    void OpenGLImguiLayerImpl::OnAttach() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui_ImplSDL2_InitForOpenGL(m_ownerWindow.GetSDLWindow(), m_ownerWindow.GetSDLGLContext());
        ImGui_ImplOpenGL3_Init("#version 460");
    }

    void OpenGLImguiLayerImpl::OnDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void OpenGLImguiLayerImpl::OnUpdate() {
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }

    void OpenGLImguiLayerImpl::ImguiFrameBegin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
    }

    void OpenGLImguiLayerImpl::ImguiFrameEnd() {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(m_ownerWindow.GetWidth(), m_ownerWindow.GetHeight());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            SDL_Window* currentWindow = SDL_GL_GetCurrentWindow();
            SDL_GLContext currentContext = SDL_GL_GetCurrentContext();
            // TODO: add implementation for mac
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(currentWindow, currentContext);
        }
    }
}
