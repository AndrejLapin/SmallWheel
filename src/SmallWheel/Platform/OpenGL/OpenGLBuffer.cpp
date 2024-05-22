#include "swpch.hpp"
#include "OpenGLBuffer.hpp"

#include "glad/gl.h"
#include "OpenGLBackend.hpp"

namespace swheel {
    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indecies, uint32_t count): m_count(count) {
        GLCall(glCreateBuffers(1, &m_rendererId));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indecies, GL_STATIC_DRAW));
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        GLCall(glDeleteBuffers(1, &m_rendererId));
    }

    void OpenGLIndexBuffer::Bind() const {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId));
    }

    void OpenGLIndexBuffer::Unbind() const {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
        GLCall(glCreateBuffers(1, &m_rendererId));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererId));
        GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        GLCall(glDeleteBuffers(1, &m_rendererId));
    }

    void OpenGLVertexBuffer::Bind() const {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererId));
    }

    void OpenGLVertexBuffer::Unbind() const {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
}
