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

# === SDL ===
# TODO: Move from caching options to compiling with options
set(SDL_TEST OFF CACHE BOOL "Don't build tests")
set(SDL_SHARED OFF CACHE BOOL "Don't build dynamic library")
add_subdirectory(SDL)
target_link_libraries(SmallWheel SDL2-static)

# === GLAD ===
add_subdirectory(GLAD)
target_link_libraries(SmallWheel GLAD)

# === imgui ===
add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD)
set(IMGUI_ADD_BACKEND_SDL ON CACHE BOOL "Add SDL backend")
set(IMGUI_ADD_BACKEND_OPENGL3 ON CACHE BOOL "Add OpenGL3 backend")
add_subdirectory(imgui)
target_link_libraries(imgui PRIVATE SDL2-static)
target_link_libraries(SmallWheel imgui)

# === glm ===
set(GLM_ENABLE_CXX_17 ON CACHE BOOL "Enable c++ 17")
# Check GLM SIMD glm options
add_subdirectory(glm)
target_include_directories(SmallWheel PUBLIC glm/)
target_link_libraries(SmallWheel glm)

target_include_directories(SmallWheel PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)

if((DEFINED SW_DEBUG_MODE) AND (${SW_DEBUG_MODE}))
    add_compile_definitions(SW_DEBUG)
endif()

# if(WIN32)
#     add_compile_definitions(SW_PLATFORM_WINDOWS)
# endif()
# add_compile_definitions(SW_BUILD_DLL)
