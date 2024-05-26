#pragma once

#include "VertexLayout.hpp"

namespace swheel {
    class MeshData {
    public:
        MeshData(const VertexLayout& layout, void* vertexData, uint32_t vertexCount, uint32_t* indecies, uint32_t indexCount);
        ~MeshData();

        const VertexLayout& GetLayout() const { return m_layout; }
        const void* GetData() const { return m_vertexData; }
        const uint32_t* GetIndices() const { return m_indecieis; }
        uint32_t GetVertexCount() const { return m_vertexCount; }
        uint32_t GetIndexCount() const { return m_indexCount; }

        VertexPropertyType GetPropertyType(const std::string& propertyName);

        template<class T>
        VertexPropertyView<T> GetPropertyView(std::string propertyName) {
            const VertexProperty& property = m_layout.GetProperty(propertyName);
            return VertexPropertyView<T>(m_layout.GetStride(), m_vertexCount, m_vertexData + property.offset);
        }

    private:
        const VertexLayout& m_layout;
        std::byte* m_vertexData;
        uint32_t m_vertexCount;
        uint32_t* m_indecieis;
        uint32_t m_indexCount;
    };
}