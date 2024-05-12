#include "OpenGLRenderer.hpp"
#include "SmallWheel/Renderer/Shader.hpp"
#include "swpch.hpp"
#include "OpenGLShader.hpp"

#include "SmallWheel/Core.hpp"
#include "SmallWheel/Utils/Result.hpp"

namespace swheel {
    OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc) {
        GLuint vertexShader;
        GLuint fragmentShader;
        {
            Result<GLuint, ShaderError> vertexShaderResult = CompileShader(vertexSrc, GL_VERTEX_SHADER);
            Result<GLuint, ShaderError> fragmentShaderResult = CompileShader(fragmentSrc, GL_FRAGMENT_SHADER);

            if (!vertexShaderResult.isValid() || !fragmentShaderResult.isValid()) {
                if (vertexShaderResult.isValid()) {
                    GLCall(glDeleteShader(vertexShaderResult.getResult()));
                } else if (fragmentShaderResult.isValid()) {
                    GLCall(glDeleteShader(fragmentShaderResult.getResult()));
                }
                return;
            }
            vertexShader = vertexShaderResult.getResult();
            fragmentShader = fragmentShaderResult.getResult();
        }

        m_rendererId = glCreateProgram();
        ShaderError error = LinkShaders({vertexShader, fragmentShader});
        if (error != ShaderError::NONE) {
            GLCall(glDeleteProgram(m_rendererId));
            GLCall(glDeleteProgram(vertexShader));
            GLCall(glDeleteProgram(fragmentShader));
        }

        // Always detach shaders after a successful link.
        GLCall(glDetachShader(m_rendererId, vertexShader));
        GLCall(glDetachShader(m_rendererId, fragmentShader));
        GLCall(glDeleteShader(vertexShader));
        GLCall(glDeleteShader(fragmentShader));
    }

    OpenGLShader::~OpenGLShader() {
        GLCall(glDeleteProgram(m_rendererId));
    }

    Shader::ShaderError OpenGLShader::LinkShaders(const std::vector<GLuint>& shaders) {
        for (auto shader : shaders) {
            GLCall(glAttachShader(m_rendererId, shader));
        }
        GLCall(glLinkProgram(m_rendererId));

        GLint isLinked = 0;
        GLCall(glGetProgramiv(m_rendererId, GL_LINK_STATUS, (int*)&isLinked));
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            GLCall(glGetProgramiv(m_rendererId, GL_INFO_LOG_LENGTH, &maxLength));

            if (maxLength > 0 ) {
                auto infoLog = std::make_unique<GLchar[]>(maxLength);
                GLCall(glGetProgramInfoLog(m_rendererId, maxLength, &maxLength, &infoLog[0]));

                std::cerr << "Shader link failure: " << infoLog.get() << '\n';
            } else {
                std::cerr << "Unknown shader link failure!\n";
            }
            SW_ASSERT(false);
            return ShaderError::LINKING_FAILED;
        }
        return ShaderError::NONE;
    }

    Result<GLuint, Shader::ShaderError> OpenGLShader::CompileShader(const std::string& shaderSource, GLenum type) {
        GLCall(GLuint shader = glCreateShader(type));

        const GLchar* source = shaderSource.c_str();
        GLCall(glShaderSource(shader, 1, &source, 0));

        GLCall(glCompileShader(shader));

        GLint isCompiled = 0;
        GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled));
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength));

            if (maxLength > 0) {
                auto infoLog = std::make_unique<GLchar[]>(maxLength);
                GLCall(glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]));

                GLCall(glDeleteShader(shader));

                std::cerr << "Shader compliation failure: " << infoLog.get() << '\n';
            } else {
                std::cerr << "Unknown shader link failure!\n";
            }

            SW_ASSERT(false);
            return Result<GLuint, ShaderError>::error(ShaderError::COMPILATION_FAILED);
        }
        return Result<GLuint, ShaderError>::valid(shader);
    }

    void OpenGLShader::Bind() const {
        GLCall(glUseProgram(m_rendererId));
    }

    void OpenGLShader::Unbind() const {
        GLCall(glUseProgram(m_rendererId));
    }
}
