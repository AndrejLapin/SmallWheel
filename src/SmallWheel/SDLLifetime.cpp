#include "swpch.hpp"
#include "SDLLifetime.hpp"

#include "SDL.h"

namespace swheel {
    SDLLifetime::SDLLifetime() {}

    SDLLifetime::~SDLLifetime() {
        SDL_Quit();
    }

    void SDLLifetime::Init() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "Failed to initialize SDL.\n";
        } else {
            std::cout << "SDL initialised.\n";
        }
    }

    void SDLLifetime::PrintSDLErrors() {
        constexpr uint16_t maxErrors = 1000;
        uint16_t currentErrors = 0;
        while (const char* error = SDL_GetError()) {
            std::cerr << error << '\n';
            if (++currentErrors >= maxErrors) {
                break;
            }
        }
    }
}
