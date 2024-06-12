#include "swpch.hpp"
#include "Application.hpp"

#include "Event.hpp"
#include "Imgui/ImguiLayer.hpp"
#include "Window.hpp"
#include "Platform/OpenGL/OpenGLWindow.hpp"
#include "SDL_timer.h"
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
            const ShaderResourceRegistry::Entry& vertex = m_shaderRegistry.GetEntry(CoreShaderRegistry::Type::COLOR_OUT_VERTEX_SHADER);
            const ShaderResourceRegistry::Entry& fragment = m_shaderRegistry.GetEntry(CoreShaderRegistry::Type::COLOR_IN_FRAGMENT_SHADER);
            m_shader = m_backend->CreateShader(vertex, fragment);
            m_shader->Load();
            shaderManager->AddShader(m_shader);
        }
    }

    /*
    I think it would make a lot of sense if rendering happend in a seperate function from Update
    First we would Update all the layers and did all the OnEvent things
    Later we would need to call render function?
    When rendering an object we need to know what shader and renderer to use to render it
    How to we choose what renderer gets used, maybe use the same renderer for everything for now
    When creating an object that will get rendered it should be part of some list if it is visible, 
    if not, we should remove it from thatl ist, or maybe just have a simple flag m_Visible
    We would have to go through all of those objects and submit them to the renderer
    Later on the renderer decides what to do with these objects,
    maybe it will need to "batch" some objects using the same shader
    although this type of batching should be happening automatically
    */

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

        float lastTime = SDL_GetTicks();
        float deltaTime = 0.0f;
        float currentTime;
        do {

            m_backend->Clear();
            mesh->Reload();
            auto& shader = *m_shader;
            m_backend->GetSimpleRenderer().DrawMesh(*m_shader, *mesh);

            currentTime = SDL_GetTicks();
            deltaTime = currentTime - lastTime;
            m_window->OnUpdate(deltaTime);
            lastTime = currentTime;

            while(event.PollNextEvent()) {
                m_window->OnEvent(event);
            }
        } while (!m_window->IsClosed());
    }

    GraphicsBackend& Application::GetGraphicsBackend() {
        SW_ASSERT_LOG(m_backend.get(),
            "Application backend has not been initialized yet! Gets initialized after \"SetConfigurationDefaults\" call.");
        return *m_backend.get();
    }


    void Application::PushLayer(RefCounted<Layer> layer) {
        SW_ASSERT_LOG(m_window.get(), "Window has not been initialized yet! Gets initialized after \"SetConfigurationDefaults\" call.");
        m_window->PushLayer(layer);
    }

    void Application::PushOverlay(RefCounted<Layer> layer) {
        SW_ASSERT_LOG(m_window.get(), "Window has not been initialized yet! Gets initialized after \"SetConfigurationDefaults\" call.");
        m_window->PushOverlay(layer);
    }
}
