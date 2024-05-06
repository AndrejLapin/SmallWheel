#pragma once

#include <string>

namespace swheel {
    class Window;

    class Application {
    public:
        Application();
        virtual ~Application();
        void CreateWindow(const std::string& title, int width, int height);

        void Run();

    private:
        void InitGlad();

    private:
        bool m_gladInitialized = false;
        Window* m_window = nullptr;
    };

    // To be defined in a Client
    Application* CreateApplication();
}
