#pragma once

#include "glm/fwd.hpp"

#include "../Camera.hpp"
#include "../Mesh.hpp"
#include "../Shader.hpp"
#include "../RendererAPIs.hpp"

namespace swheel {
    class SimpleMeshRender {
    public:
        SimpleMeshRender(RendererAPI api): m_API(api) {}
        void DrawMesh(Shader& shader, Mesh& mesh) const;

        void BeginScene(Camera& camera);
        // I think mesh should have parameters like uniforms and shader included in it
        void SubmitMesh(Shader& shader, Mesh& mesh);
        //void EndScene(); // end scene should submit everything to the graphics api in an order that was decided by the renderer

    private:
        glm::mat4 view;
        glm::mat4 projection;
        const RendererAPI m_API;
    };
}
