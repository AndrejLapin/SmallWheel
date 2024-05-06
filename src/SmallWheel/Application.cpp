#include "Application.hpp"
#include "SDL.h"
#include "SDL_error.h"
#include "SDL_video.h"
#include "Windowing/Window.hpp"
#include "Windowing/OpenGLWindow.hpp"
#include "glad/gl.h"
#include "Event.hpp"

#include <iostream>
#include <cassert>

namespace swheel {

    Application::Application() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "Failed to initialize SDL.\n";
        } else {
            std::cout << "SDL initialised.\n";
        }
        SDL_GL_LoadLibrary(nullptr);
        std::cout << "SDL application created\n";

        // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        // SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    }

    Application::~Application() {
        delete m_window;
    }

    void Application::CreateWindow(const std::string& title, int width, int height) {
        // Maybe make it so you can create multiple windows?
        assert(!m_window);
        m_window = new OpenGLWindow(title, width, height);

        if (!m_gladInitialized) {
            InitGlad();
        }
    }

    void Application::Run() {
        while (!m_window->IsClosed()) {
            Event event;
            while(SDL_PollEvent(&event)) {
                m_window->OnEvent(event);
            }
        }
    }

    void Application::InitGlad() {
        int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
        if (version == 0) {
            std::cerr << "SDL error: " << SDL_GetError() << "\n";
            std::cerr << "Failed to initialize OpenGL context :(\n";
            exit(1);
        }
        std::cout << "OpenGL Info:\n";
        std::cout << " Vendor: " << glGetString(GL_VENDOR) << '\n';
        std::cout << " Renderer: " << glGetString(GL_RENDERER) << '\n';
        std::cout << " Version: " << glGetString(GL_VERSION) << '\n';
    }
}
