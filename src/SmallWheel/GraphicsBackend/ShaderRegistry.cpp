#include "swpch.hpp"
#include <filesystem>
#include "ShaderRegistry.hpp"

namespace swheel {
    // NEED STB LIBRARY FOR THIS
    const std::filesystem::path shaderRegistry::s_colorOutVertexShader = "../SmallWheel/res/shaders/glsl/ColorOut.vert";
    const std::filesystem::path shaderRegistry::s_colorInFragmentShader = "../SmallWheel/res/shaders/glsl/ColorIn.frag";
}
