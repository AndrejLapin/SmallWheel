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
        default: SW_ASSERT_LOG(false, "Unknown VertexPropertyType!");
        }
        return 0;
    }

    uint32_t VertexDataTypeElementCount(VertexPropertyType type) {
        switch (type) {
        case VertexPropertyType::Float:     return 1;
        case VertexPropertyType::Float2:    return 2;
        case VertexPropertyType::Float3:    return 3;
        case VertexPropertyType::Float4:    return 4;
        default: SW_ASSERT_LOG(false, "Unknown VertexPropertyType!");
        }
        return 0;
    }

    VertexLayout::VertexLayout(const std::initializer_list<InitializerVertexProperty>& elements) {
        std::vector<InitializerVertexProperty> initializerElements(elements);

        for (auto& element : elements) {
            Result<const VertexProperty*, VertexLayout::LayoutError> result = GetPropertyImpl(element.name);
            SW_ASSERT_LOG(!result.isSuccess(), "Value with name: " + element.name + " already exists!");
            m_properties.emplace_back(VertexProperty{m_stride, element.type, element.name});
            m_stride += VertexDataTypeSize(element.type);
        }
    }

    const VertexProperty& VertexLayout::GetProperty(const std::string& propertyName) const {
        Result<const VertexProperty*, VertexLayout::LayoutError> result = GetPropertyImpl(propertyName);
        SW_ASSERT_LOG(result.isSuccess(), "Element with name: " + propertyName + " does not exist in the layout.");
        return *result.getResult();
    }

    Result<const VertexProperty*, VertexLayout::LayoutError> VertexLayout::GetPropertyImpl(const std::string& propertyName) const {
        for (auto& it : m_properties) {
            if (it.name == propertyName) {
                return Result<const VertexProperty*, VertexLayout::LayoutError>::success(&it);
            }
        }
        return Result<const VertexProperty*, VertexLayout::LayoutError>::error(LayoutError::PROPERTY_NOT_FOUND);
    }
}
