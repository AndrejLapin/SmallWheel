#pragma once

namespace swheel {
    template<typename T>
    class RefCounted {
    public:
        RefCounted() = default;

        RefCounted(const RefCounted& other): m_ptr(other.m_ptr) {
            IncrementRefCount();
        }

        RefCounted& operator=(const RefCounted& other) {
            DecrementRefCount();
            m_ptr = other.m_ptr;
            IncrementRefCount();
            return *this;
        }

        ~RefCounted() {
            DecrementRefCount();
        }

        template<typename... Args>
        static RefCounted<T> Make(Args&&... args) {
            void* allocation = std::malloc(sizeof(uint32_t) + sizeof(T));
            uint32_t* refCount = reinterpret_cast<uint32_t*>(allocation);
            *refCount = 1;
            T* data = reinterpret_cast<T*>(refCount + 1);
            new(data) T(std::forward<Args>(args)...);
            return RefCounted<T>(data);
        }

        T* operator ->() {
            return m_ptr;
        }

        T& operator *() {
            return m_ptr;
        }

    private:
        explicit RefCounted(T* ptr): m_ptr(ptr) {}

        void IncrementRefCount() {
            uint32_t* refCount = reinterpret_cast<uint32_t*>(m_ptr) - 1;
            ++(*refCount);
        }

        void DecrementRefCount() {
            if (!m_ptr) {
                return;
            }
            uint32_t* refCount = reinterpret_cast<uint32_t*>(m_ptr) - 1;
            --(*refCount);
            if ((*refCount) == 0) {
                m_ptr->~T();
                std::free(refCount);
            }
        }

    private:
        T* m_ptr = nullptr;
    };
}
