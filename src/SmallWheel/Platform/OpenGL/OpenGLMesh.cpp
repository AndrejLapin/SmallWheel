#include "OpenGLMesh.hpp"
#include "OpenGLBackend.hpp"
#include "SmallWheel/Core.hpp"
#include "SmallWheel/GraphicsBackend/VertexLayout.hpp"
#include <cstdint>

namespace swheel {
    OpenGLMesh::~OpenGLMesh() {
        if (m_loaded) {
            Unload();
        }
    }

    void OpenGLMesh::Load() {
        GLCall(glGenVertexArrays(1, &m_vertexArray));
        GLCall(glBindVertexArray(m_vertexArray));

        const VertexLayout& layout = m_meshData.GetLayout();

        // we could create vertex and index buffer here at the same time
        GLCall(glGenBuffers(1, &m_vertexBuffer));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer));
        // what is the static draw for? read into this
        GLCall(glBufferData(GL_ARRAY_BUFFER, m_meshData.GetVertexCount() * layout.GetStride(), m_meshData.GetData(), GL_STATIC_DRAW));

        {
            uint32_t currentAttribute = 0;
            for (auto& properyt : layout) {
                GLCall(glEnableVertexAttribArray(currentAttribute));
                uint32_t count = VertexDataTypeElementCount(properyt.type);
                // can be something other than GL_FLOAT, implement
                GLCall(glVertexAttribPointer(currentAttribute, count, GL_FLOAT, GL_FALSE, layout.GetStride(), reinterpret_cast<const void*>(properyt.offset)));
                currentAttribute++;
            }
        }

        GLCall(glGenBuffers(1, &m_indexBuffer));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_meshData.GetIndexCount() * sizeof(uint32_t), m_meshData.GetIndices(), GL_STATIC_DRAW));

        m_loaded = true;
        Unbind();
    }

    void OpenGLMesh::Unload() {
        SW_ASSERT_LOG(m_loaded, "Mesh not loaded!");
        GLCall(glDeleteVertexArrays(1, &m_vertexArray));
        // probvably possible to delte two at a time
        GLCall(glDeleteBuffers(1, &m_vertexBuffer));
        GLCall(glDeleteBuffers(1, &m_indexBuffer));
    }

    void OpenGLMesh::Bind() {
        SW_ASSERT_LOG(m_loaded, "Mesh not loaded!");
        GLCall(glBindVertexArray(m_vertexArray));
    }

    void OpenGLMesh::Unbind() {
        SW_ASSERT_LOG(m_loaded, "Mesh not loaded!");
        GLCall(glBindVertexArray(0));
    }
}
