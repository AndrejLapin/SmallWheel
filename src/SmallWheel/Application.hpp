#pragma once

namespace swheel {
    using ApplicationWindow = void*;
    class Window;

    // SDL based application
    class Application {
    public:
        Application();
        virtual ~Application();

        // This needs to return something like window ID so the user can manage it
        ApplicationWindow CreateWindow(const std::string& title, int width, int height);

        void Run();

    private:
        void InitGlad();

    private:
        bool m_gladInitialized = false;
        std::vector<std::unique_ptr<Window>> m_windows;
    };

    // To be defined in a Client
    Application* CreateApplication();
}
