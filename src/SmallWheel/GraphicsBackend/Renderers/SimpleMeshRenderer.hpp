#pragma once

#include "../Mesh.hpp"
#include "../Shader.hpp"
#include "../RendererAPIs.hpp"

namespace swheel {
    class SimpleMeshRender {
    public:
        SimpleMeshRender(RendererAPI api): m_API(api) {}
        void DrawMesh(Shader& shader, Mesh& mesh) const;

    private:
        const RendererAPI m_API;
    };
}
