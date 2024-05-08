#pragma once

namespace swheel {
    class Window;

    // SDL based application
    class Application {
    public:
        Application(const std::string& title, int width, int height);
        virtual ~Application();

        void Run();

    private:
        void CreateWindow(const std::string& title, int width, int height);
        void InitGlad();

    private:
        std::unique_ptr<Window> m_window;
    };

    // To be defined in a Client
    Application* CreateApplication();
}
