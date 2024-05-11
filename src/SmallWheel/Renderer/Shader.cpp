#include "swpch.hpp"
#include "Shader.hpp"

#include "SmallWheel/Core.hpp"
#include "SmallWheel/Utils/Result.hpp"

namespace swheel {
    Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc) {
        GLuint vertexShader;
        GLuint fragmentShader;
        {
            Result<GLuint, ShaderError> vertexShaderResult = CompileShader(vertexSrc, GL_VERTEX_SHADER);
            Result<GLuint, ShaderError> fragmentShaderResult = CompileShader(fragmentSrc, GL_FRAGMENT_SHADER);

            if (!vertexShaderResult.isValid() || !fragmentShaderResult.isValid()) {
                if (vertexShaderResult.isValid()) {
                    glDeleteShader(vertexShaderResult.getResult());
                } else if (fragmentShaderResult.isValid()) {
                    glDeleteShader(fragmentShaderResult.getResult());
                }
                return;
            }
            vertexShader = vertexShaderResult.getResult();
            fragmentShader = fragmentShaderResult.getResult();
        }

        m_rendererId = glCreateProgram();

        ShaderError error = LinkShaders({vertexShader, fragmentShader});
        if (error != ShaderError::NONE) {
            glDeleteProgram(m_rendererId);
            glDeleteProgram(vertexShader);
            glDeleteProgram(fragmentShader);
        }

        // Always detach shaders after a successful link.
        glDetachShader(m_rendererId, vertexShader);
        glDetachShader(m_rendererId, fragmentShader);
    }

    Shader::~Shader() {
        glDeleteProgram(m_rendererId);
    }

    Shader::ShaderError Shader::LinkShaders(const std::vector<GLuint>& shaders) {
        for (auto shader : shaders) {
            glAttachShader(m_rendererId, shader);
        }
        glLinkProgram(m_rendererId);

        GLint isLinked = 0;
        glGetProgramiv(m_rendererId, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(m_rendererId, GL_INFO_LOG_LENGTH, &maxLength);

            if (maxLength > 0 ) {
                auto infoLog = std::make_unique<GLchar[]>(maxLength);
                glGetProgramInfoLog(m_rendererId, maxLength, &maxLength, &infoLog[0]);

                std::cerr << "Shader link failure: " << infoLog.get() << '\n';
            } else {
                std::cerr << "Unknown shader link failure!\n";
            }
            SW_ASSERT(false);
            return ShaderError::LINKING_FAILED;
        }
        return ShaderError::NONE;
    }

    Result<GLuint, Shader::ShaderError> Shader::CompileShader(const std::string& shaderSource, GLenum type) {
        GLuint shader = glCreateShader(type);

        const GLchar* source = shaderSource.c_str();
        glShaderSource(shader, 1, &source, 0);

        glCompileShader(shader);

        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            if (maxLength > 0) {
                auto infoLog = std::make_unique<GLchar[]>(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                glDeleteShader(shader);

                std::cerr << "Shader compliation failure: " << infoLog.get() << '\n';
            } else {
                std::cerr << "Unknown shader link failure!\n";
            }

            SW_ASSERT(false);
            return Result<GLuint, ShaderError>::error(ShaderError::COMPILATION_FAILED);
        }
        return Result<GLuint, ShaderError>::valid(shader);
    }

    void Shader::Bind() const {
        glUseProgram(m_rendererId);
    }

    void Shader::Unbind() const {
        glUseProgram(m_rendererId);
    }
}
