#pragma once

#include <filesystem>

namespace swheel {
    struct shaderRegistry {
        static const std::filesystem::path s_colorOutVertexShader;
        static const std::filesystem::path s_colorInFragmentShader;
    };
}