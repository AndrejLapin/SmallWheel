#include "SmallWheel/Core.hpp"
#include "swpch.hpp"
#include <cstdint>
#include "MeshData.hpp"

namespace swheel {
    MeshData::MeshData(const VertexLayout& layout, float* vertexData, uint32_t vertexCount, uint32_t* indecies, uint32_t indexCount): 
    m_layout(layout), m_vertexCount(vertexCount), m_indexCount(indexCount) {
        SW_ASSERT_LOG(vertexData && indecies, "Vertex data and index data cannot be empty!");
        uint32_t vertexEntryCount = m_vertexCount * m_layout.GetStride() / sizeof(float);
        m_vertexData = new float[vertexEntryCount];
        std::memcpy(m_vertexData, vertexData, vertexEntryCount * sizeof(float));
        m_indecieis = new uint32_t[m_indexCount];
        std::memcpy(m_indecieis, indecies, m_indexCount * sizeof(uint32_t));
    }

    MeshData::~MeshData() {
        delete[] m_vertexData;
        delete[] m_indecieis;
    }

    VertexPropertyType MeshData::GetPropertyType(const std::string& propertyName) {
        return m_layout.GetProperty(propertyName).type;
    }
}
