#include "Application.hpp"
#include "Windowing/SDL2Window.hpp"

namespace swheel {

    Application::Application() {
    }

    Application::~Application() {
        delete m_window;
    }

    void Application::CreateWindow(const std::string& title, int width, int height) {
        // Maybe make it so you can create multiple windows?
        if (!m_window) {
            m_window = new SDL2Window(title, width, height);
        }
    }

    void Application::Run() {
        while (m_window && !m_window->IsClosed()) {
            m_window->PollEvents();
        }
    }
}