#pragma once

#include "SmallWheel/GraphicsBackend/Mesh.hpp"
#include "SmallWheel/GraphicsBackend/MeshData.hpp"
#include "glad/gl.h"

namespace swheel {
    class OpenGLMesh : public Mesh {
    public:
        OpenGLMesh(const MeshData& mesh): Mesh(mesh) {}
        ~OpenGLMesh();

        void Load() override;
        void Unload() override;
        void Bind() override;
        void Unbind() override;
        bool IsLoaded() override { return m_loaded; }
    
    private:
        GLuint m_vertexArray = 0;
        GLuint m_vertexBuffer = 0;
        GLuint m_indexBuffer = 0;
        bool m_loaded = false;
    };
}
