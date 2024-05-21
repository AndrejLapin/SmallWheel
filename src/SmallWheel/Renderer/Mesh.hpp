#pragma once

#include "VertexLayout.hpp"
#include "SmallWheel/Platform/OpenGL/OpenGLMeshData.h"

namespace swheel {
    class Mesh {
    public:
        Mesh(const VertexLayout& layout, float* vertexData, uint32_t vertexCount, uint32_t* indecies, uint32_t indexCount);
        ~Mesh();

        const VertexLayout& GetLayout() const { return m_layout; }
        VertexPropertyType GetPropertyType(const std::string& propertyName);

        template<class T>
        VertexPropertyView<T> GetPropertyView(std::string propertyName) {
            const VertexProperty& property = m_layout.GetProperty(propertyName);
            return VertexPropertyView<T>(m_layout.GetStride(), m_vertexCount, reinterpret_cast<short*>(m_vertexData) + property.offset);
        }

    private:
        const VertexLayout& m_layout;
        float* m_vertexData;
        uint32_t m_vertexCount;
        uint32_t* m_indecieis;
        uint32_t m_indexCount;
        // Maybe this should not be a union?
        // Each api should be able to have it's own data seperately
        // Or a specific version of a mesh for specific API should be created?
        union {
            struct OpenGLMeshData;
        }m_graphicsAPIData;
    };
}