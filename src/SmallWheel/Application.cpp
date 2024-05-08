#include <swpch.hpp>
#include "Application.hpp"

#include "SDL.h"
#include "SDL_error.h"
#include "SDL_video.h"
#include "Windowing/Window.hpp"
#include "Windowing/OpenGLWindow.hpp"
#include "glad/gl.h"
#include "Event.hpp"

namespace swheel {

    Application::Application(const std::string& title, int width, int height) {
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

        CreateWindow(title, width, height);

        InitGlad();
    }

    Application::~Application() {
        SDL_Quit();
    }

    void Application::CreateWindow(const std::string& title, int width, int height) {
        m_window = std::make_unique<OpenGLWindow>(title, width, height);
    }

    void Application::Run() {
        Event event;
        do {
            while(event.PollNextEvent()) {
                m_window->OnEvent(event);
            }
        } while (!m_window->IsClosed());
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
