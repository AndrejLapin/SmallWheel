#pragma once

namespace swheel {
    class Window;
    class Shader;

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
        std::unique_ptr<Shader> m_shader;
        std::unique_ptr<Window> m_window;

        unsigned int m_vertexArray, m_vertexBuffer, m_indexBuffer;
    };

    // To be defined in a Client
    Application* CreateApplication();
}
