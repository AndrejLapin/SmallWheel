#pragma once

#include "GraphicsBackend/ShaderResourceRegistry.hpp"

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
        const ShaderResourceRegistry::Entry& GetEntry(Type type) const; 

    private:
        ShaderResourceRegistry registry;
    };
}
