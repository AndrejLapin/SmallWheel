#pragma once

#include <string>

namespace swheel {
    class SDL2Window;

    class Application {
    public:
        Application();
        virtual ~Application();
        void CreateWindow(const std::string& title, int width, int height);

        void Run();
    private:
        SDL2Window* m_window = nullptr;
    };

    // To be defined in a Client
    Application* CreateApplication();
}