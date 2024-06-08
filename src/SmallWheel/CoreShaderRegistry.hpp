#pragma once

#include "GraphicsBackend/ShaderRegistry.hpp"

namespace swheel {
    class CoreShaderRegistry {
    public:
        enum class Type: uint16_t {
            COLOR_OUT_VERTEX_SHADER,
            COLOR_IN_FRAGMENT_SHADER,
            TOTAL
        };

    public:
        CoreShaderRegistry() = default;
        CoreShaderRegistry(const std::string& resourcesPath);
        const ShaderRegistry::Entry& GetEntry(Type type) const; 

    private:
        ShaderRegistry registry;
    };
}
