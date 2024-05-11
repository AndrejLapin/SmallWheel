#pragma once

#include "SmallWheel/Renderer/Buffer.hpp"

namespace swheel {
    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t* indecies, uint32_t count);
        ~OpenGLIndexBuffer();

        void Bind() const override;
        void Unbind() const override;
        uint32_t GetCount() const override { return m_count; }

    private:
        uint32_t m_rendererId;
        uint32_t m_count;
    };

    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        ~OpenGLVertexBuffer();

        void Bind() const override;
        void Unbind() const override;
    private:
        uint32_t m_rendererId;
    };
}
