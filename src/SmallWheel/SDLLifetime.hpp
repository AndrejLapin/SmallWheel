#pragma once

namespace swheel {
    class SDLLifetime {
    public:
        SDLLifetime();
        ~SDLLifetime();
        void Init();
        static void PrintSDLErrors();
    };
}