#include "swpch.hpp"
#include "ShaderRegistry.hpp"

#include "SmallWheel/Core.hpp"

namespace swheel {
    // NEED STB LIBRARY FOR THIS
    ShaderRegistry::Entry::Entry(std::filesystem::path openGLPath): m_openGLPath(openGLPath) {}

    const std::filesystem::path& ShaderRegistry::Entry::GetPath(RendererAPI api) const {
        switch (api) {
        case RendererAPI::OpenGL: return m_openGLPath;
        }
        SW_ASSERT_LOG(false, "Unknown API type!");
    }

    const ShaderRegistry::Entry& ShaderRegistry::GetEntry(uint16_t type) const {
        // TODO: make this safe
        const std::optional<Entry>& entry = m_entries[static_cast<uint16_t>(type)];
        SW_ASSERT_LOG(entry.has_value(), "Shader value not initialized at type: " + std::to_string(static_cast<uint16_t>(type)));
        return entry.value();
    }
}
