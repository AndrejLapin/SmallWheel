#pragma once

#include "SmallWheel/Core.hpp"
#include "SmallWheel/Utils/Result.hpp"

namespace swheel {
    namespace propertyUnion {
        union Single {
            float data;
        };

        union Pair {
            struct {
                float x, y;
            };
            struct {
                float u, v;
            };
        };

        union Triple {
            struct {
                float x, y, z;
            };
            struct {
                float r, g, b;
            };
        };

        union Quad {
            struct {
                float x, y, z, w;
            };
            struct {
                float r, g, b, a;
            };
        };
    }

    enum class VertexPropertyType {
        None,
        Float,
        Float2,
        Float3,
        Float4
    };

    // Has yet to be tested
    // Maybe unit tests should be created?
    template<class T>
    class VertexPropertyView {
    public:
        class Iterator {
        public:
            Iterator(uint32_t stride, std::byte* data):
                m_stride(stride), m_ptr(data) {}

            T& operator*() { return *reinterpret_cast<T*>(m_ptr); }
            const T& operator*() const { return *reinterpret_cast<T*>(m_ptr); }

            Iterator& operator++() {
                m_ptr += m_stride;
                return *this;
            }

            Iterator operator++(int) {
                Iterator result = *this;
                m_ptr += m_stride;
                return result;
            }

            Iterator& operator--() {
                m_ptr -= m_stride;
                return *this;
            }

            Iterator operator--(int) {
                Iterator result = *this;
                m_ptr -= m_stride;
                return result;
            }

            bool operator==(const Iterator& other) const { return m_ptr == other.m_ptr; }
            bool operator!=(const Iterator& other) const { return m_ptr != other.m_ptr; }

            private:
                std::byte* m_ptr;
                uint32_t m_stride;
        };

    public:
        VertexPropertyView(uint32_t stride, uint32_t count, void* data):
            m_stride(stride), m_count(count), m_data(reinterpret_cast<std::byte*>(data)) {}
        
        T& operator[](std::size_t index) { return *reinterpret_cast<T*>(m_data + (index * m_stride)); }
        const T& operator[](std::size_t index) const { return *reinterpret_cast<T*>(m_data + (index * m_stride)); }
        uint32_t GetCount() { return m_count; }

        Iterator begin() const { return Iterator(m_stride, m_data); }
        Iterator end()   const { return Iterator(m_stride, m_data + (m_count * m_stride)); }

    private:
        std::byte* m_data;
        uint32_t m_count;
        uint32_t m_stride;
    };

    uint32_t VertexDataTypeSize(VertexPropertyType type);
    uint32_t VertexDataTypeElementCount(VertexPropertyType type);

    struct VertexProperty {
        uint32_t offset;
        VertexPropertyType type;
        std::string name;
    };

    struct InitializerVertexProperty {
        VertexPropertyType type;
        std::string name;
    };

    class VertexLayout {
    private:
        enum class LayoutError {
            PROPERTY_NOT_FOUND
        };
    public:
        VertexLayout(const std::initializer_list<InitializerVertexProperty>& elements);

        const VertexProperty& GetProperty(const std::string& propertyName) const;
        uint32_t GetStride() const { return m_stride; }

        std::vector<VertexProperty>::iterator begin() { return m_properties.begin(); }
        std::vector<VertexProperty>::const_iterator begin() const { return m_properties.begin(); }

        std::vector<VertexProperty>::iterator end() { return m_properties.end(); }
        std::vector<VertexProperty>::const_iterator end() const { return m_properties.end(); }
    private:
        Result<const VertexProperty*, LayoutError> GetPropertyImpl(const std::string& propertyName) const;

    private:
        std::vector<VertexProperty> m_properties;
        uint32_t m_stride = 0;
    };
}
