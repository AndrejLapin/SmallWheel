#pragma once

#include "SDLLifeTime.hpp"
#include "GraphicsBackend/MeshData.hpp"
#include "SmallWheel/GraphicsBackend/MeshData.hpp"
#include "SmallWheel/GraphicsBackend/GraphicsBackend.hpp"

namespace swheel {
    class Window;
    class Shader;
    class IndexBuffer;
    class VertexBuffer;

    // SDL based application
    class Application {
    public:
        struct SharedData {
            MeshData* meshData = nullptr;
        };

        Application(const std::string& title, int width, int height);
        virtual ~Application();

        void Run();

    private:
        SDLLifetime m_sdlLifetime;
        std::unique_ptr<GraphicsBackend> m_backend;
        std::unique_ptr<Window> m_window;
        std::unique_ptr<Shader> m_shader;
        SharedData m_sharedData;
    };

    // To be defined in a Client
    Application* CreateApplication();
}
