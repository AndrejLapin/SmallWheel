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
        mesh.Unbind();
        shader.Unbind();
    }

    
    void SimpleMeshRender::BeginScene(Camera& camera) {
        // we have to set the camera view and projection matricies
        view = camera.GetProjectionMatrix();
        projection = glm::inverse(camera.GetTransform());
    }


    void SimpleMeshRender::SubmitMesh(Shader& shader, Mesh& mesh) {
        mesh.Bind();
        shader.Bind();
        // also apply MVP uniform
        // this probably has to be moved to API related 
        switch (m_API) {
        case RendererAPI::OpenGL: {
            GLCall(glDrawElements(GL_TRIANGLES, mesh.GetData().GetIndexCount(), GL_UNSIGNED_INT, nullptr));
        }break;
        }
        mesh.Unbind();
        shader.Unbind();
    }
}
