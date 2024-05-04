#include "Application.hpp"
#include "SDL.h"
#include "SDL_error.h"
#include "SDL_video.h"
#include "Windowing/SDL2Window.hpp"
#include "glad/gl.h"

#include <iostream>
#include <cassert>

namespace swheel {
    // maybe create a better way to manage this static variable,
    // global is not as nice
    static bool s_SDLInitialised = false;

    Application::Application() {
    }

    Application::~Application() {
        delete m_window;
    }

    void Application::CreateWindow(const std::string& title, int width, int height) {
        // Should be done once per application
        if (!s_SDLInitialised) {
            // Might need to SDL_INIT_EVERYTHING
            if (SDL_Init(SDL_INIT_VIDEO) != 0) {
                std::cerr << "Failed to initialize SDL.\n";
            } else {
                s_SDLInitialised = true;
                std::cout << "SDL initialised.\n";
            }
        }

        SDL_GL_LoadLibrary(nullptr);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

        // Maybe make it so you can create multiple windows?
        // gladLoaderLoadGL()
        assert(!m_window);
        m_window = new SDL2Window(title, width, height);

        auto error = SDL_GetError();
        if (error && error[0] != 0) {
            std::cerr << error << "\n";
        }

        int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
        if (version == 0) {
            std::cerr << "SDL error: " << SDL_GetError() << "\n";
            std::cerr << "Failed to initialize OpenGL context :(\n";
            exit(1);
        }
        std::cout << glGetError << "\n";
        std::cout << "GL version - " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << "\n";
    }

    void Application::Run() {
        while (m_window && !m_window->IsClosed()) {
            m_window->PollEvents();
        }
    }
}