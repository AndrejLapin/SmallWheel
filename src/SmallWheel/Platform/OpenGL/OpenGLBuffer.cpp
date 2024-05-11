#include "swpch.hpp"
#include "OpenGLBuffer.hpp"

#include "glad/gl.h"
#include <cstdint>

namespace swheel {
    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indecies, uint32_t count): m_count(count) {
        glCreateBuffers(1, &m_rendererId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indecies, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        glDeleteBuffers(1, &m_rendererId);
    }

    void OpenGLIndexBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
    }

    void OpenGLIndexBuffer::Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
        glCreateBuffers(1, &m_rendererId);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        glDeleteBuffers(1, &m_rendererId);
    }

    void OpenGLVertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
    }

    void OpenGLVertexBuffer::Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
