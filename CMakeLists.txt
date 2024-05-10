cmake_minimum_required(VERSION 3.25)
project(SmallWheel VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

file(GLOB_RECURSE PROJECT_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(PROJECT_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/)


add_library(SmallWheel STATIC ${PROJECT_SOURCE})
target_include_directories(SmallWheel PRIVATE ${PROJECT_INCLUDES})
target_precompile_headers(SmallWheel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/swpch.hpp)

set(SDL_TEST FALSE)
set(SDL_SHARED FALSE)
add_subdirectory(SDL)
# target_include_directories
target_link_libraries(SmallWheel SDL2-static)

add_subdirectory(GLAD)
target_link_libraries(SmallWheel GLAD)

if((DEFINED SW_DEBUG_MODE) AND (${SW_DEBUG_MODE}))
    add_compile_definitions(SW_DEBUG)
endif()

# if(WIN32)
#     add_compile_definitions(SW_PLATFORM_WINDOWS)
# endif()
# add_compile_definitions(SW_BUILD_DLL)
