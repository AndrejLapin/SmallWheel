#include "SDL2Window.hpp"

#include "SDL.h"
#include "SDL_events.h"
#include <iostream>

namespace swheel {
    SDL2Window::SDL2Window(const std::string& title, int width, int height):
    m_title(title), m_width(width), m_height(height) {
        if (!Init()) {
            m_closed = true;
        }
    }

    SDL2Window::~SDL2Window() {
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    bool SDL2Window::Init() {
        // Might need to SDL_INIT_EVERYTHING
        // Maybe SDL initialization should be global/shared between many windows
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "Failed to initialize SDL.\n";
            return false;
        }

        m_window = SDL_CreateWindow(
            m_title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            m_width, m_height,
            0
        );

        if (m_window == nullptr) {
            std::cerr << "Failed to create window.\n";
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