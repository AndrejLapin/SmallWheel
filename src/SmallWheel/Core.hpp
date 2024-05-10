#pragma once

#ifdef SW_DEBUG
    #define SW_ENABLE_ASSERTS
#endif

#ifdef SW_ENABLE_ASSERTS
    #define SW_ASSERT(condition, ...) do{ if(!(condition)) { std::cerr << __VA_ARGS__ << '\n'; assert(false); } }while(0)
#else
    #define SW_ASSERT(condition, ...)
#endif

#define SW_VALIDATE(condition, onError, ...) SW_ASSERT(condition, __VA_ARGS__); onError
