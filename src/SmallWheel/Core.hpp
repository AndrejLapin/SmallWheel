#pragma once
#include "Utils/LogUtils.hpp"

#ifdef SW_DEBUG
    #define SW_ENABLE_LOGGING
    #define SW_ENABLE_ASSERTS
    #define SW_ENABLE_GRAPHICS_DEBUG
#endif

#ifdef SW_ENABLE_LOGGING
    #define SW_LOG(...) do { swheel::log::Info(__VA_ARGS__); }while(0)
    #define SW_ERROR_LOG(...) do { swheel::log::Error(__VA_ARGS__); }while(0)
#else
    #define SW_LOG(message)
    #define SW_ERROR_LOG(message)
#endif

#ifdef SW_ENABLE_ASSERTS
    #define SW_ASSERT(condition) do { assert(condition); }while(0)
    #define SW_ASSERT_LOG(condition, ...) do{ if(!(condition)) { SW_ERROR_LOG(__VA_ARGS__); assert(false); } }while(0)
#else
    #define SW_ASSERT(condition)
    #define SW_ASSERT_LOG(condition, ...)
#endif

// TODO: fis this up later
// #define SW_VALIDATE(condition, onError) 
// User has to put a ';' at the end
#define SW_VALIDATE_LOG(condition, onError, ...) if(!(condition)) { SW_ASSERT_LOG(condition, __VA_ARGS__); onError; }
