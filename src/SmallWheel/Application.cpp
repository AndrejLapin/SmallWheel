#include "SmallWheel/GraphicsBackend/RendererAPIs.hpp"
#include "swpch.hpp"
#include "Application.hpp"

#include "glad/gl.h"
#include "Event.hpp"
#include "Window.hpp"
#include "Platform/OpenGL/OpenGLWindow.hpp"
#include "Imgui/ImguiLayer.hpp"
#include "GraphicsBackend/Shader.hpp"
#include "GraphicsBackend/GraphicsBackend.hpp"
#include "GraphicsBackend/VertexLayout.hpp"
#include "GraphicsBackend/CommonVertexLayouts.hpp"
#include "GraphicsBackend/Renderers/SimpleMeshRenderer.hpp"
#include "GraphicsBackend/Mesh.hpp"
#include "GraphicsBackend/MeshData.hpp"
#include "GraphicsBackend/ShaderRegistry.hpp"

namespace swheel {

    Application::Application(const std::string& title, int width, int height) {
        m_sdlLifetime.Init();

        m_backend = GraphicsBackend::CreateBackend(RendererAPI::OpenGL);

        m_window = m_backend->CreateWindow(title, width, height);

        const GraphicsBackend& graphicsBackend = m_window->GetGraphicsBackend();
        m_window->PushOverlay<ImguiLayer>(m_sharedData, "Imgui");
        m_shader = graphicsBackend.CreateShader(shaderRegistry::s_colorOutVertexShader, shaderRegistry::s_colorInFragmentShader);
        m_shader->Load();
    }

    Application::~Application() {
    }

    void Application::Run() {
        Event event;

        float vertices[3 * 7] = {
            -0.8f,  -0.5f, 0.0f,     1.0f, 0.0f, 0.0f, 1.0f,
            0.2f,  -0.5f, 0.0f,      0.0f, 1.0f, 0.0f, 1.0f,
            -0.3f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f, 
        };
        unsigned int indecies[3] = { 0, 1, 2 };
        MeshData meshData(commonLayouts::PositionColor::Layout(), vertices, 3, indecies, 3);
        m_sharedData.meshData = &meshData;
        std::unique_ptr<Mesh> mesh = m_backend->CreateMeshInstance(meshData);
        mesh->Load();

        do {
            m_backend->Clear();
            mesh->Reload();
            m_backend->GetSimpleRenderer().DrawMesh(*m_shader, *mesh);
            m_window->OnUpdate();

            while(event.PollNextEvent()) {
                m_window->OnEvent(event);
            }
        } while (!m_window->IsClosed());
    }
}
