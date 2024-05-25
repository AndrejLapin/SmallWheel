#pragma once

#include "Buffer.hpp"
#include "Mesh.hpp"
#include "MeshData.hpp"
#include "Shader.hpp"
#include "RendererAPIs.hpp"
#include "Renderers/SimpleMeshRenderer.hpp"
#include "SmallWheel/Window.hpp"

namespace swheel {
    class GraphicsBackend {
    public:
        explicit GraphicsBackend(RendererAPI type): m_type(type) {}
        virtual ~GraphicsBackend() {}

        virtual void Clear() const = 0;

        //static std::unique_ptr<GraphicsBackend> CreateBackend(RendererAPI type);

        // Maybe this should be managed by the shader itself?
        std::unique_ptr<Shader> CreateShader(const std::string& vetexSrc, const std::string& fragmentSrc) const;
        std::unique_ptr<IndexBuffer> CreateIndexBuffer(uint32_t* indecies, uint32_t size) const;
        std::unique_ptr<VertexBuffer> CreateVertexBuffer(float* vertices, uint32_t size) const;
        std::unique_ptr<Mesh> CreateMeshInstance(const MeshData& meshData) const;

        SimpleMeshRender GetSimpleRenderer() const;

        RendererAPI GetAPIType() const { return m_type; }

    private:
        RendererAPI m_type;
    };
}
