#pragma once

#include "Buffer.hpp"
#include "Shader.hpp"

namespace swheel {
    enum class RendererAPI {
        OpenGL
    };

    class GraphicsBackend {
    public:
        explicit GraphicsBackend(RendererAPI type): m_type(type) {}
        virtual ~GraphicsBackend() {}

        virtual void Clear() const = 0;
        virtual void Draw(const VertexBuffer& va, const IndexBuffer& ib, const Shader& shader) const = 0;

        // should actually be a renderer
        static std::unique_ptr<GraphicsBackend> CreateRenderer(RendererAPI type);

        // Maybe this should be managed by the shader itself?
        std::unique_ptr<Shader> CreateShader(const std::string& vetexSrc, const std::string& fragmentSrc) const;
        std::unique_ptr<IndexBuffer> CreateIndexBuffer(uint32_t* indecies, uint32_t size) const;
        std::unique_ptr<VertexBuffer> CreateVertexBuffer(float* vertices, uint32_t size) const;

        RendererAPI GetAPIType() const { return m_type; }

    private:
        RendererAPI m_type;
    };
}
