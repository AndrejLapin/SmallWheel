cmake_minimum_required(VERSION 3.25)
project(SmallWheel VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB_RECURSE PROJECT_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(SmallWheel ${PROJECT_SOURCE})

if(CMAKE_GENERATOR_PLATFORM MATCHES "x64")
    message(STATUS "Building for x64 architecture")
else()
    message(FATAL_ERROR "This CMakeLists.txt supports only x64 architecture.")
endif()
