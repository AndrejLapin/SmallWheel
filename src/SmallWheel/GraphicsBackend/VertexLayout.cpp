#include "swpch.hpp"
#include "VertexLayout.hpp"

#include "SmallWheel/Core.hpp"

namespace swheel {
    uint32_t VertexDataTypeSize(VertexPropertyType type) {
        switch (type) {
        case VertexPropertyType::Float:     return 4;
        case VertexPropertyType::Float2:    return 4 * 2;
        case VertexPropertyType::Float3:    return 4 * 3;
        case VertexPropertyType::Float4:    return 4 * 4;
        }
        SW_ASSERT_LOG(false, "Unknown VertexPropertyType!");
        return 0;
    }

    uint32_t VertexDataTypeElementCount(VertexPropertyType type) {
        switch (type) {
        case VertexPropertyType::Float:     return 1;
        case VertexPropertyType::Float2:    return 2;
        case VertexPropertyType::Float3:    return 3;
        case VertexPropertyType::Float4:    return 4;
        }
        SW_ASSERT_LOG(false, "Unknown VertexPropertyType!");
        return 0;
    }

    VertexLayout::VertexLayout(const std::initializer_list<InitializerVertexProperty>& elements) {
        std::vector<InitializerVertexProperty> initializerElements(elements);

        for (auto& element : elements) {
            const auto& result = m_properties.try_emplace(element.name, VertexProperty{m_stride, element.type});
            SW_ASSERT_LOG(result.second, "Value with name: " + element.name + " already exists!");
            m_stride += VertexDataTypeSize(element.type);
        }
    }

    const VertexProperty& VertexLayout::GetProperty(const std::string& elementName) const {
        auto it = m_properties.find(elementName);
        SW_ASSERT_LOG(it != m_properties.end(), "Element with name: " + elementName + " does not exist in the layout.");
        return it->second;
    }
}
