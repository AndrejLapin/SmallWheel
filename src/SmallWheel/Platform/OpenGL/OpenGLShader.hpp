#pragma once

#include "glad/gl.h"
#include "SmallWheel/GraphicsBackend/Shader.hpp"
#include "SmallWheel/Utils/Result.hpp"

namespace swheel {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& vetexSrc, const std::string& fragmentSrc);
        ~OpenGLShader();

        void Bind() const override;
        void Unbind() const override;

    private:
        ShaderError LinkShaders(const std::vector<GLuint>& shaders);
        Result<GLuint, ShaderError> CompileShader(const std::string& shaderSource, GLenum type);

    private:
        uint32_t m_rendererId;
    };
}
