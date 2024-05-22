#include "OpenGLMesh.hpp"
#include "OpenGLBackend.hpp"
#include "SmallWheel/GraphicsBackend/VertexLayout.hpp"

namespace swheel {
    OpenGLMesh::~OpenGLMesh() {
        Unload();
    }

    void OpenGLMesh::Load() {
        GLCall(glGenVertexArrays(1, &m_vertexArray));
        GLCall(glBindVertexArray(m_vertexArray));

        // we could create vertex and index buffer here at the same time
        GLCall(glCreateBuffers(1, &m_vertexBuffer));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer));
        // what is the static draw for? read into this
        GLCall(glBufferData(GL_ARRAY_BUFFER, m_meshData.GetVertexCount() * sizeof(float), m_meshData.GetData(), GL_STATIC_DRAW));

        {
            const VertexLayout& layout = m_meshData.GetLayout();
            uint32_t currentAttribute = 0;
            for (auto& [key, properyt] : layout) {
                GLCall(glEnableVertexAttribArray(currentAttribute));
                uint32_t count = VertexDataTypeElementCount(properyt.type);
                // can be something other than GL_FLOAT, implement
                GLCall(glVertexAttribPointer(currentAttribute, count, GL_FLOAT, GL_FALSE, layout.GetStride(), nullptr));
                currentAttribute++;
            }
        }

        GLCall(glCreateBuffers(1, &m_indexBuffer));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_meshData.GetIndexCount() * sizeof(uint32_t), m_meshData.GetIndices(), GL_STATIC_DRAW));

        Unbind();
    }

    void OpenGLMesh::Unload() {
        GLCall(glDeleteVertexArrays(1, &m_vertexArray));
        // probvably possible to delte two at a time
        GLCall(glDeleteBuffers(1, &m_vertexBuffer));
        GLCall(glDeleteBuffers(1, &m_indexBuffer));
    }

    void OpenGLMesh::Bind() {
        GLCall(glBindVertexArray(m_vertexArray));
    }

    void OpenGLMesh::Unbind() {
        GLCall(glBindVertexArray(0));
    }
}
