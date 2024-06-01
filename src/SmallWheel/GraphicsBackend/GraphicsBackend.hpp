#pragma once

#include "Buffer.hpp"
#include "MeshData.hpp"
#include "RendererAPIs.hpp"
#include "Renderers/SimpleMeshRenderer.hpp"

namespace swheel {
    class Shader;
    class IndexBuffer;
    class VertexBuffer;
    class Mesh;
    class Window;

    class GraphicsBackend {
    public:
        explicit GraphicsBackend(RendererAPI type): m_type(type) {}
        virtual ~GraphicsBackend() {}

        static std::unique_ptr<GraphicsBackend> CreateBackend(RendererAPI type);

        virtual void Clear() const = 0;

        virtual std::unique_ptr<Window> CreateWindow(const std::string& title, int width, int height) const;
        virtual std::unique_ptr<Shader> CreateShader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath) const;
        virtual std::unique_ptr<IndexBuffer> CreateIndexBuffer(uint32_t* indecies, uint32_t size) const;
        virtual std::unique_ptr<VertexBuffer> CreateVertexBuffer(float* vertices, uint32_t size) const;
        virtual std::unique_ptr<Mesh> CreateMeshInstance(const MeshData& meshData) const;

        SimpleMeshRender GetSimpleRenderer() const;

        RendererAPI GetAPIType() const { return m_type; }

    private:
        RendererAPI m_type;
    };
}
