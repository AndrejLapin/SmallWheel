#include "swpch.hpp"
#include "SDLLifetime.hpp"

#include "SDL.h"
#include "Core.hpp"

namespace swheel {
    SDLLifetime::SDLLifetime() {}

    SDLLifetime::~SDLLifetime() {
        SDL_Quit();
    }

    void SDLLifetime::Init() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            SW_ERROR_LOG("Failed to initialize SDL.");
        } else {
            SW_LOG("SDL initialised.");
        }
    }

    void SDLLifetime::PrintSDLErrors() {
        constexpr uint16_t maxErrors = 1000;
        uint16_t currentErrors = 0;
        while (const char* error = SDL_GetError()) {
            SW_ERROR_LOG(error);
            if (++currentErrors >= maxErrors) {
                break;
            }
        }
    }
}
