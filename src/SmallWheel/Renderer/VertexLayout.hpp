#pragma once

#include "SmallWheel/Core.hpp"

namespace swheel {
    enum class VertexDataType {
        None,
        Float,
        Float2,
        Float3,
        Float4
    };

    uint32_t VertexDataTypeSize(VertexDataType type);

    struct BufferElement {
        uint32_t offset;
        VertexDataType type;
    };

    struct InitializerBufferElement {
        VertexDataType type;
        std::string name;
    };

    class VertexLayout {
    public:
        VertexLayout(const std::initializer_list<InitializerBufferElement>& elements);

    private:
        std::map<std::string, BufferElement> m_elements;
        uint32_t m_stride = 0;
    };
}
