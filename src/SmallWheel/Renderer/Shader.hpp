#pragma once

#include "glad/gl.h"
#include "SmallWheel/Utils/Result.hpp"

namespace swheel {
    class Shader {
    public:
        enum class ShaderError : uint32_t {
            NONE = 0,
            COMPILATION_FAILED,
            LINKING_FAILED
        };

        Shader(const std::string& vetexSrc, const std::string& fragmentSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;

    private:
        ShaderError LinkShader(GLuint shader);
        Result<GLuint, ShaderError> CompileShader(const std::string& shaderSource, GLenum type);


    private:
        uint32_t m_rendererId;
    };
}
