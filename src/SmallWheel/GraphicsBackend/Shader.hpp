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

        virtual void Load() = 0;
        virtual void Unload() = 0;
        virtual void Reload() = 0;
        virtual void TryReload() = 0;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
    };
}
