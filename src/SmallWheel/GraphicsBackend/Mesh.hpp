#pragma once

#include "VertexLayout.hpp"

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
            return VertexPropertyView<T>(m_layout.GetStride(), m_vertexCount, m_vertexData + property.offset);
        }

    private:
        const VertexLayout& m_layout;
        float* m_vertexData;
        uint32_t m_vertexCount;
        uint32_t* m_indecieis;
        uint32_t m_indexCount;
    };
}