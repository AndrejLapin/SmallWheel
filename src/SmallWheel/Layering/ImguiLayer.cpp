#include "SDL_video.h"
#include "SmallWheel/Platform/OpenGL/OpenGLWindow.hpp"
#include "swpch.hpp"
#include "ImguiLayer.hpp"

#include "SDL_timer.h"
#include "imgui.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/backends/imgui_impl_opengl3.h"

namespace swheel {
    ImguiLayer::ImguiLayer(const Window& owner, const std::string& name): 
        Layer(owner, name), 
        m_ownerOpenGLWindow(*static_cast<const OpenGLWindow*>(&owner)) {
    }

    ImguiLayer::~ImguiLayer() {

    }

    void ImguiLayer::OnAttach() {
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

        ImGui_ImplSDL2_InitForOpenGL(m_ownerOpenGLWindow.GetSDLWindow(), m_ownerOpenGLWindow.GetSDLGLContext());
        ImGui_ImplOpenGL3_Init("#version 460");
    }

    void ImguiLayer::OnDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void ImguiLayer::OnUpdate() {
        ImguiFrameBegin();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImguiFrameEnd();
    }

    void ImguiLayer::OnEvent(Event& event) {
        event.m_handled = ImGui_ImplSDL2_ProcessEvent(&event.m_event);
    }

    void ImguiLayer::ImguiFrameBegin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
    }

    void ImguiLayer::ImguiFrameEnd() {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(m_ownerOpenGLWindow.GetWidth(), m_ownerOpenGLWindow.GetHeight());

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
