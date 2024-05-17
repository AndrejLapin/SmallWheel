#pragma once

#include "SDLLifeTime.hpp"

namespace swheel {
    class Window;
    class Shader;
    class IndexBuffer;
    class VertexBuffer;

    // SDL based application
    class Application {
    public:
        Application(const std::string& title, int width, int height);
        virtual ~Application();

        void Run();

    private:
        void PrintSDLErrors();
        void InitGlad();

    private:
        SDLLifetime sdlLifetime;
        std::unique_ptr<Window> m_window;
        std::unique_ptr<Shader> m_shader;
        std::unique_ptr<IndexBuffer> m_indexBuffer;
        std::unique_ptr<VertexBuffer> m_vertexBuffer;

        unsigned int m_vertexArray;//, m_indexBuffer;
    };

    // To be defined in a Client
    Application* CreateApplication();
}
