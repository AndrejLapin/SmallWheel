#pragma once

#include <memory>
#include <string>
#include <vector>

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
        std::vector<std::unique_ptr<Window>> m_windows;
    };

    // To be defined in a Client
    Application* CreateApplication();
}
