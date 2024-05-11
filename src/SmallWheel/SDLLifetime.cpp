#include "swpch.hpp"
#include "SDLLifetime.hpp"

#include "SDL.h"

namespace swheel {
    SDLLifetime::SDLLifetime() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "Failed to initialize SDL.\n";
        } else {
            std::cout << "SDL initialised.\n";
        }
    }

    SDLLifetime::~SDLLifetime() {
        SDL_Quit();
    }
}
