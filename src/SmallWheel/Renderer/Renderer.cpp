#include "swpch.hpp"
#include "Renderer.hpp"

#include "SmallWheel/Core.hpp"
#include "SmallWheel/Platform/OpenGL/OpenGLBuffer.hpp"
#include "SmallWheel/Platform/OpenGL/OpenGLRenderer.hpp"
#include "SmallWheel/Platform/OpenGL/OpenGLShader.hpp"

namespace swheel {
    std::unique_ptr<Renderer> Renderer::CreateRenderer(RendererAPI type) {
        switch (type) {
        case RendererAPI::OpenGL: return std::make_unique<OpenGLRenderer>();
        }
        SW_ASSERT(false);
    }

    std::unique_ptr<Shader> Renderer::CreateShader(const std::string& vetexSrc, const std::string& fragmentSrc) const {
        switch (m_type) {
        case RendererAPI::OpenGL: return std::make_unique<OpenGLShader>(vetexSrc, fragmentSrc);
        }
        SW_ASSERT(false);
    }

    std::unique_ptr<IndexBuffer> Renderer::CreateIndexBuffer(uint32_t* indecies, uint32_t size) const {
        switch (m_type) {
        case RendererAPI::OpenGL: return std::make_unique<OpenGLIndexBuffer>(indecies, size);
        }
        SW_ASSERT(false);
    }

    std::unique_ptr<VertexBuffer> Renderer::CreateVertexBuffer(float* vertices, uint32_t size) const {
        switch (m_type) {
        case RendererAPI::OpenGL: return std::make_unique<OpenGLVertexBuffer>(vertices, size);
        }
        SW_ASSERT(false);
    }
}
