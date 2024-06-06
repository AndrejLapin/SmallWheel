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

    ShaderRegistry::ShaderRegistry(const std::string& resourcesPath) {
        m_entries.resize(static_cast<uint32_t>(Type::TOTAL));

        m_entries[static_cast<uint32_t>(Type::COLOR_OUT_VERTEX_SHADER)].emplace(resourcesPath + "shaders/glsl/ColorOut.vert");
        m_entries[static_cast<uint32_t>(Type::COLOR_IN_FRAGMENT_SHADER)].emplace(resourcesPath + "shaders/glsl/ColorIn.frag");
    }

    const ShaderRegistry::Entry& ShaderRegistry::GetEntry(Type type) const {
        // TODO: make this safe
        const std::optional<Entry>& entry = m_entries[static_cast<uint32_t>(type)];
        SW_ASSERT_LOG(entry.has_value(), "Shader value not initialized at type: " + std::to_string(static_cast<uint32_t>(type)));
        return entry.value();
    }
}
