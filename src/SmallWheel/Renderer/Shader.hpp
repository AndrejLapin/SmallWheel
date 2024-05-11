#pragma once

namespace swheel {
    class Shader {
    public:
        enum class ShaderError : uint32_t {
            NONE = 0,
            COMPILATION_FAILED,
            LINKING_FAILED
        };

        virtual ~Shader() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
    };
}
