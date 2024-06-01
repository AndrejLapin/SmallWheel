#include "RendererAPIs.hpp"
#include "Renderers/SimpleMeshRenderer.hpp"
#include "swpch.hpp"
#include "GraphicsBackend.hpp"

#include "SmallWheel/Core.hpp"
#include "SmallWheel/Platform/OpenGL/OpenGLBuffer.hpp"
#include "SmallWheel/Platform/OpenGL/OpenGLBackend.hpp"
#include "SmallWheel/Platform/OpenGL/OpenGLShader.hpp"
#include "SmallWheel/Platform/OpenGL/OpenGLMesh.hpp"
#include "SmallWheel/Platform/OpenGL/OpenGLWindow.hpp"

namespace swheel {
    std::unique_ptr<GraphicsBackend> GraphicsBackend::CreateBackend(RendererAPI type) {
        switch (type) {
        case RendererAPI::OpenGL: return std::make_unique<OpenGLBackend>();
        }
        SW_ASSERT(false);
    }

    std::unique_ptr<Window> GraphicsBackend::CreateWindow(const std::string& title, int width, int height) const {
        switch (m_type) {
        case RendererAPI::OpenGL: return std::make_unique<OpenGLWindow>(*this, title, width, height);
        }
        SW_ASSERT(false);
    }

    std::unique_ptr<Shader> GraphicsBackend::CreateShader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath) const {
        switch (m_type) {
        case RendererAPI::OpenGL: return std::make_unique<OpenGLShader>(vertexPath, fragmentPath);
        }
        SW_ASSERT(false);
    }

    std::unique_ptr<IndexBuffer> GraphicsBackend::CreateIndexBuffer(uint32_t* indecies, uint32_t size) const {
        switch (m_type) {
        case RendererAPI::OpenGL: return std::make_unique<OpenGLIndexBuffer>(indecies, size);
        }
        SW_ASSERT(false);
    }

    std::unique_ptr<VertexBuffer> GraphicsBackend::CreateVertexBuffer(float* vertices, uint32_t size) const {
        switch (m_type) {
        case RendererAPI::OpenGL: return std::make_unique<OpenGLVertexBuffer>(vertices, size);
        }
        SW_ASSERT(false);
    }

    std::unique_ptr<Mesh> GraphicsBackend::CreateMeshInstance(const MeshData& meshData) const {
        switch (m_type) {
        case RendererAPI::OpenGL: return std::make_unique<OpenGLMesh>(meshData);
        }
        SW_ASSERT(false);
    }

    SimpleMeshRender GraphicsBackend::GetSimpleRenderer() const {
        return SimpleMeshRender(m_type);
    }
}
