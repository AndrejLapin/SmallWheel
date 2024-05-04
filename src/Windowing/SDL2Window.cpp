#include "SDL2Window.hpp"

#include "SDL.h"
#include "SDL_events.h"
#include <cstddef>
#include <iostream>

namespace swheel {
    SDL2Window::SDL2Window(const std::string& title, int width, int height):
    m_title(title), m_width(width), m_height(height) {
        if (!Init()) {
            m_closed = true;
        }
    }

    SDL2Window::~SDL2Window() {
        SDL_GL_DeleteContext(m_context);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    bool SDL2Window::Init() {
        m_window = SDL_CreateWindow(
            m_title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            m_width, m_height,
            SDL_WINDOW_OPENGL
        );

        if (m_window == nullptr) {
            std::cerr << "Failed to create window.\n";
            return false;
        }

        m_context = SDL_GL_CreateContext(m_window);

        if (m_context == nullptr) {
            std::cerr << "OpenGL context not avalibale\n";
            return false;
        }

        return true;
    }

    void SDL2Window::PollEvents() {
        SDL_Event event;

        if (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT: {
                m_closed = true;
                break;
            }
            default: {
                break;
            }
            }
        }
    }
}