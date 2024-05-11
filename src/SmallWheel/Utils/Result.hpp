#pragma once

#include "SmallWheel/Core.hpp"

namespace swheel {
    template<typename T, typename E>
    class Result {
    public:
        static Result valid(T result) {
            return Result(result);
        }

        static Result error(E error) {
            return Result(error);
        }

        bool isValid() const {
            return std::holds_alternative<T>(m_data);
        }

        const T& getResult() const {
            SW_ASSERT(std::holds_alternative<T>(m_data));
            return std::get<T>(m_data);
        }

        const E& getError() const {
            SW_ASSERT(std::holds_alternative<E>(m_data));
            return std::get<E>(m_data);
        }

    private:
        explicit Result(T result): m_data(result) {}
        explicit Result(E error): m_data(error) {}

    private:
        std::variant<T, E> m_data;
    };
}
