#pragma once

#include "SmallWheel/GraphicsBackend/Mesh.hpp"
#include "SmallWheel/GraphicsBackend/MeshData.hpp"
#include "glad/gl.h"

namespace swheel {
    class OpenGLMesh : Mesh {
    public:
        OpenGLMesh(const MeshData& mesh): Mesh(mesh) {}
        ~OpenGLMesh();

        void Load() override;
        void Unload() override;
        void Bind() override;
        void Unbind() override;
    
    private:
        GLuint m_vertexArray;
        GLuint m_vertexBuffer;
        GLuint m_indexBuffer;
    };
}
