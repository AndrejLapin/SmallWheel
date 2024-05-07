#pragma once

#include "ApplicationWindow.hpp"
#include "Window.hpp"
#include <vector>

namespace swheel {
    class WindowManager {
    public:
        WindowManager() = default;
        ~WindowManager() = default;

        ApplicationWindow AddWindow(std::unique_ptr<Window> window);
    private:
        std::vector<std::unique_ptr<Window>> m_windows;
        std::vector<ApplicationWindow> m_windowReferences; // should this be pointers or something???, maybe they are a pointer to something
    };
}