#include "swpch.hpp"
#include "VertexLayout.hpp"

#include "SmallWheel/Core.hpp"

namespace swheel {
    uint32_t VertexDataTypeSize(VertexDataType type) {
        switch (type) {
        case VertexDataType::Float:     return 4;
        case VertexDataType::Float2:    return 4 * 2;
        case VertexDataType::Float3:    return 4 * 3;
        case VertexDataType::Float4:    return 4 * 4;
        }
        SW_ASSERT_LOG(false, "Unknown VertexDataType!");
        return 0;
    }

    VertexLayout::VertexLayout(const std::initializer_list<InitializerBufferElement>& elements) {
        std::vector<InitializerBufferElement> initializerElements(elements);

        for (auto& element : elements) {
            const auto& result = m_elements.try_emplace(element.name, BufferElement{m_stride, element.type});
            SW_ASSERT_LOG(result.second, "Value with name: " + element.name + " already exists!");
            m_stride += VertexDataTypeSize(element.type);
        }
    }
}
