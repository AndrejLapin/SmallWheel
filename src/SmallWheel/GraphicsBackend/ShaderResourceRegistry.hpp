#pragma once

#include "RendererAPIs.hpp"

namespace swheel {
    class ShaderResourceRegistry {
    public:
        class Entry {
        public:
            Entry(std::filesystem::path openGLPath);
            const std::filesystem::path& GetPath(RendererAPI api) const;

        private:
            const std::filesystem::path m_openGLPath;
        };

    public:
        ShaderResourceRegistry() = default;
        const Entry& GetEntry(uint16_t type) const; 
        std::vector<std::optional<Entry>>& GetEntries() { return m_entries; }

    private:
        std::vector<std::optional<Entry>> m_entries;
    };
}