#pragma once

#include "Shader.hpp"
#include "MeshData.hpp"

namespace swheel {
    class Mesh {
    public:
        Mesh(const MeshData& meshData): m_meshData(meshData) {}
        virtual ~Mesh() {}

        virtual void Load() = 0;
        virtual void Unload() = 0;
        virtual void Reload() = 0;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual bool IsLoaded() = 0;
        const MeshData& GetData() const { return m_meshData; }

    protected:
        const MeshData& m_meshData;
    };
}
