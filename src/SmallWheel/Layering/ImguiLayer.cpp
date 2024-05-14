#include "SDL_stdinc.h"
#include "swpch.hpp"
#include "ImguiLayer.hpp"

// #include "imgui"

#include "SDL_timer.h"
#include "imgui.h"
#include "SmallWheel/Platform/OpenGL/OpenGLimguiRenderer.hpp"

namespace swheel {
    ImguiLayer::ImguiLayer(): m_time(SDL_GetTicks()) {

    }

    ImguiLayer::~ImguiLayer() {

    }

    void ImguiLayer::OnAttach() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui_ImplOpenGL3_Init("#version 460");
    }

    void ImguiLayer::OnDetach() {

    }

    void ImguiLayer::OnUpdate() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGuiIO& io = ImGui::GetIO();
        // layer should probably have a refference to their window?
        io.DisplaySize = ImVec2(1600, 800);
        ImGui::NewFrame();

        Uint32 time = SDL_GetTicks();
        io.DeltaTime = m_time > 0 ? (time - m_time) / 1000.0f : (1.0f / 60.0f);
        m_time = time;

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
