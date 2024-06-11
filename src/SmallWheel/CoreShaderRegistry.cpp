#include "swpch.hpp"
#include "CoreShaderRegistry.hpp"

namespace swheel {
    CoreShaderRegistry::CoreShaderRegistry(const std::string& resourcesPath) {
        std::vector<std::optional<ShaderResourceRegistry::Entry>>& entries = registry.GetEntries();

        entries.resize(static_cast<uint32_t>(Type::TOTAL));

        entries[static_cast<uint32_t>(Type::COLOR_OUT_VERTEX_SHADER)].emplace(resourcesPath + "shaders/glsl/ColorOut.vert");
        entries[static_cast<uint32_t>(Type::COLOR_IN_FRAGMENT_SHADER)].emplace(resourcesPath + "shaders/glsl/ColorIn.frag");
    }
     
    const ShaderResourceRegistry::Entry& CoreShaderRegistry::GetEntry(Type type) const {
        return registry.GetEntry(static_cast<uint16_t>(type));
    }
}
