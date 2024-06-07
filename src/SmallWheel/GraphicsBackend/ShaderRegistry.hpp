#pragma once

#include "RendererAPIs.hpp"

namespace swheel {
    class ShaderRegistry {
    public:
        // make small wheel wrapper for this instead
        enum class Type: uint32_t {
            COLOR_OUT_VERTEX_SHADER,
            COLOR_IN_FRAGMENT_SHADER,
            TOTAL
        };

        class Entry {
        public:
            Entry(std::filesystem::path openGLPath);
            const std::filesystem::path& GetPath(RendererAPI api) const;

        private:
            const std::filesystem::path m_openGLPath;
        };

    public:
        ShaderRegistry() = default;
        ShaderRegistry(const std::string& resourcesPath);
        const Entry& GetEntry(Type type) const; 

    private:
        std::vector<std::optional<Entry>> m_entries;
    };
}