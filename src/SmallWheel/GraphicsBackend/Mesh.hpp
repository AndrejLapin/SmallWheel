#pragma once

#include "Shader.hpp"
#include "MeshData.hpp"

namespace swheel {
    class Mesh {
    public:
        Mesh(const MeshData& meshData): m_meshData(meshData) {}

        virtual void Load() = 0;
        virtual void Unload() = 0;
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual bool IsLoaded() = 0;
        const MeshData& GetData() const { return m_meshData; }

    protected:
        const MeshData& m_meshData;
    };
}
