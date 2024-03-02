#pragma once

#include "SmallWheel/Defines.hpp"

namespace swheel {
    class SWHEEL_API Application {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    // To be defined in a Client
    Application* CreateApplication();
}