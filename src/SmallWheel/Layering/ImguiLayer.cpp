#include "SDL_video.h"
#include "SmallWheel/Platform/OpenGL/OpenGLWindow.hpp"
#include "swpch.hpp"
#include "ImguiLayer.hpp"

#include "SDL_timer.h"
#include "imgui.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/backends/imgui_impl_opengl3.h"

namespace swheel {
    ImguiLayer::ImguiLayer(Window& owner, const std::string& name): Layer(owner, name), m_time(SDL_GetTicks()) {

    }

    ImguiLayer::~ImguiLayer() {

    }

    void ImguiLayer::OnAttach() {
        // TODO: implement type check here
        m_ownerOpenGLWindow = (OpenGLWindow*)&m_ownerWindow;

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

        ImGui_ImplSDL2_InitForOpenGL(m_ownerOpenGLWindow->GetSDLWindow(), m_ownerOpenGLWindow->GetSDLGLContext());
        ImGui_ImplOpenGL3_Init("#version 460");
    }

    void ImguiLayer::OnDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void ImguiLayer::OnUpdate() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(m_ownerOpenGLWindow->GetWidth(), m_ownerOpenGLWindow->GetHeight());

        // Uint32 time = SDL_GetTicks();
        // io.DeltaTime = m_time > 0 ? (time - m_time) / 1000.0f : (1.0f / 60.0f);
        // m_time = time;

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
