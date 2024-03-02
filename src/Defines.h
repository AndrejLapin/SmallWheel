#pragma once

#ifdef SW_PLATFORM_WINDOWS
    #ifdef SW_BUILD_DLL
        #define SWHEEL_API __declspec(dllexport)
    #else
        #define SWHEEL_API __declspec(dllimport)
    #endif
#else
    #error SmallWheel only supports windows
#endif

#ifdef TEST_DEFINE
    #define POOPY "poopy"
#else
    #define POOPY "Not poopy"
#endif
