#include "swpch.hpp"
#include "Application.hpp"

#include "Event.hpp"
#include "Imgui/ImguiLayer.hpp"
#include "Window.hpp"
#include "Platform/OpenGL/OpenGLWindow.hpp"
#include "SmallWheel/GraphicsBackend/RendererAPIs.hpp"
#include "SmallWheel/Layering/ShaderManagerLayer.hpp"
#include "Utils/RefCounted.hpp"
#include "GraphicsBackend/Shader.hpp"
#include "GraphicsBackend/GraphicsBackend.hpp"
#include "GraphicsBackend/VertexLayout.hpp"
#include "GraphicsBackend/CommonVertexLayouts.hpp"
#include "GraphicsBackend/Renderers/SimpleMeshRenderer.hpp"
#include "GraphicsBackend/Mesh.hpp"
#include "GraphicsBackend/MeshData.hpp"

namespace swheel {

    Application::Application() {
    }

    Application::~Application() {
    }

    void Application::InitialiseApplication(EngineConfiguration& configuration) {
        // do things

        SetConfigurationDefaults(configuration);

        // maybe things below have to be moved to "SetConfigurationDefaults"?
        if (configuration.GetWindowName().empty()) {
            configuration.SetWindowName("SmallWheel");
        }

        {
            bool dirty = false;
            std::pair<int, int> windowSize = configuration.GetWindowSize();
            if (windowSize.first <= 0) {
                dirty = true;
                windowSize.first = 1600;
            }

            if (windowSize.second <= 0) {
                dirty = true;
                windowSize.second = 800;
            }

            configuration.SetWindowSize(windowSize.first, windowSize.second);
        }

        if (configuration.GetResourcesPath().empty()) {
            configuration.SetResourcesPath("../SmallWheel/res/");
        }

        m_sdlLifetime.Init();

        m_backend = GraphicsBackend::CreateBackend(RendererAPI::OpenGL);

        {
            const std::pair<int, int>& windowSize = configuration.GetWindowSize();
            m_window = m_backend->CreateWindow(configuration.GetWindowName(),
                windowSize.first, windowSize.second);
        }

        auto imguiLayer = RefCounted<ImguiLayer>::Make(m_sharedData, "Imgui");

        m_window->PushOverlay(imguiLayer);

        m_shaderRegistry = CoreShaderRegistry(configuration.GetResourcesPath());

        {
            auto shaderManager = RefCounted<ShaderManagerLayer>::Make();
            m_window->PushOverlay(shaderManager);
            const ShaderRegistry::Entry& vertex = m_shaderRegistry.GetEntry(CoreShaderRegistry::Type::COLOR_OUT_VERTEX_SHADER);
            const ShaderRegistry::Entry& fragment = m_shaderRegistry.GetEntry(CoreShaderRegistry::Type::COLOR_IN_FRAGMENT_SHADER);
            m_shader = m_backend->CreateShader(vertex, fragment);
            m_shader->Load();
            shaderManager->AddShader(m_shader);
        }
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
            auto& shader = *m_shader;
            m_backend->GetSimpleRenderer().DrawMesh(*m_shader, *mesh);
            m_window->OnUpdate();

            while(event.PollNextEvent()) {
                m_window->OnEvent(event);
            }
        } while (!m_window->IsClosed());
    }
}
