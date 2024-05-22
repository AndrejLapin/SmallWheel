#pragma once

#include "MeshData.hpp"

namespace swheel {
    class Mesh {
    public:
        Mesh(const MeshData& meshData): m_meshData(meshData) {}

        virtual void Load() = 0;
        virtual void Unload() = 0;
        virtual void Bind() = 0;
        virtual void Unbind() = 0;

    protected:
        const MeshData& m_meshData;
    };
}
