#pragma once

#include "EngineConfiguration.hpp"
#include "SDLLifetime.hpp"
#include "GraphicsBackend/MeshData.hpp"
#include "GraphicsBackend/GraphicsBackend.hpp"
#include "SmallWheel/CoreShaderRegistry.hpp"
#include "Utils/RefCounted.hpp"

namespace swheel {
    class Window;
    class Shader;
    class IndexBuffer;
    class Layer;
    class VertexBuffer;

    // SDL based application
    class Application {
    public:
        struct SharedData {
            MeshData* meshData = nullptr;
        };

        Application();
        virtual ~Application();

        virtual void SetConfigurationDefaults(EngineConfiguration& configuration) {};
        virtual void OnApplicationInitialized() {};
        void InitialiseApplication(EngineConfiguration& configuration);
        void Run();
    
    protected:
        GraphicsBackend& GetGraphicsBackend();
        void PushLayer(RefCounted<Layer> layer);
        void PushOverlay(RefCounted<Layer> layer);

    private:
        SDLLifetime m_sdlLifetime;
        std::unique_ptr<GraphicsBackend> m_backend;
        std::unique_ptr<Window> m_window;
        RefCounted<Shader> m_shader;
        SharedData m_sharedData;
        CoreShaderRegistry m_shaderRegistry;
    };

    // To be defined in a Client
    Application* CreateApplication();
}
