#include "swpch.hpp"
#include "Mesh.hpp"

namespace swheel {
    Mesh::Mesh(const VertexLayout& layout, float* vertexData, uint32_t vertexCount, uint32_t* indecies, uint32_t indexCount): 
    m_layout(layout), m_vertexCount(vertexCount), m_indecieis() {
        m_vertexData = new float[m_vertexCount];
        std::memcpy(m_vertexData, vertexData, m_vertexCount * sizeof(float));
        m_indecieis = new uint32_t[m_indexCount];
        std::memcpy(m_indecieis, indecies, m_indexCount * sizeof(uint32_t));
    }

    Mesh::~Mesh() {
        delete[] m_vertexData;
        delete[] m_indecieis;
    }

    VertexPropertyType Mesh::GetPropertyType(const std::string& propertyName) {
        return m_layout.GetProperty(propertyName).type;
    }
}
