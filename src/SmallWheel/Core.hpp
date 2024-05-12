#pragma once

#define GlCall(x)

#ifdef SW_DEBUG
    #define SW_ENABLE_ERROR_LOGS
    #define SW_ENABLE_ASSERTS
    #define SW_ENABLE_GRAPHICS_DEBUG
#endif

// TODO: implement later
// #ifdef SW_ENABLE_ERROR_LOGS
//     #define SW_ERROR_LOG(format)
// #else
// #endif

#ifdef SW_ENABLE_ASSERTS
    #define SW_ASSERT(condition) do { assert(condition); }while(0)
    #define SW_ASSERT_LOG(condition, ...) do{ if(!(condition)) { std::cerr << __VA_ARGS__ << '\n'; assert(false); } }while(0)
#else
    #define SW_ASSERT(condition)
    #define SW_ASSERT_LOG(condition, ...)
#endif

// TODO: fis this up later
// #define SW_VALIDATE(condition, onError) 
// User has to put a ';' at the end
#define SW_VALIDATE_LOG(condition, onError, ...) if(!(condition)) { SW_ASSERT_LOG(condition, __VA_ARGS__); onError; }
