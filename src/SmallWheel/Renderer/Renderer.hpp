#pragma once

#include "Buffer.hpp"
#include "Shader.hpp"

namespace swheel {
    enum class RendererAPI {
        OpenGL
    };

    class Renderer {
    public:
        explicit Renderer(RendererAPI type): m_type(type) {}
        virtual ~Renderer() {}

        virtual void Clear() const = 0;
        virtual void Draw(const VertexBuffer& va, const IndexBuffer& ib, const Shader& shader) const = 0;

        static std::unique_ptr<Renderer> CreateRenderer(RendererAPI type);

        // Maybe this should be managed by the shader itself?
        std::unique_ptr<Shader> CreateShader(const std::string& vetexSrc, const std::string& fragmentSrc) const;
        std::unique_ptr<IndexBuffer> CreateIndexBuffer(uint32_t* indecies, uint32_t size) const;
        std::unique_ptr<VertexBuffer> CreateVertexBuffer(float* vertices, uint32_t size) const;

    private:
        RendererAPI m_type;
    };
}
