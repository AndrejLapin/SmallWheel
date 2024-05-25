#include "swpch.hpp"
#include "SimpleMeshRenderer.hpp"

#include "SmallWheel/GraphicsBackend/GraphicsBackend.hpp"
#include "SmallWheel/GraphicsBackend/Mesh.hpp"
#include "SmallWheel/GraphicsBackend/Shader.hpp"
#include "glad/gl.h"

#include "SmallWheel/Platform/OpenGL/OpenGLBackend.hpp"

namespace swheel {
    void SimpleMeshRender::DrawMesh(Shader& shader, Mesh& mesh) const {
        mesh.Bind();
        shader.Bind();
        // this probably has to be moved to API related 
        switch (m_API) {
        case RendererAPI::OpenGL: {
            GLCall(glDrawElements(GL_TRIANGLES, mesh.GetData().GetIndexCount(), GL_UNSIGNED_INT, nullptr));
        }break;
        }
    }
}
