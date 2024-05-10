#include "SmallWheel/Core.hpp"
#include "SmallWheel/Utils/Result.hpp"
#include "swpch.hpp"
#include "Shader.hpp"

#include <array>
#include <cassert>
#include <cstdint>
#include <variant>
#include <vector>

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

        uint32_t results = (uint32_t)LinkShader(vertexShader) | (uint32_t)LinkShader(fragmentShader);
        if (results) {
            glDeleteProgram(m_rendererId);
            glDeleteProgram(vertexShader);
            glDeleteProgram(fragmentShader);
        }

        // Always detach shaders after a successful link.
        glDetachShader(m_rendererId, vertexShader);
        glDetachShader(m_rendererId, fragmentShader);
    }

    Shader::ShaderError Shader::LinkShader(GLuint shader) {
        glAttachShader(m_rendererId, shader);

        GLint isLinked = 0;
        glGetProgramiv(m_rendererId, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(m_rendererId, GL_INFO_LOG_LENGTH, &maxLength);

            // Don't really need this to be an std::vector, just an array allocated at runtime
            // and then deleted when the scope is exited
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_rendererId, maxLength, &maxLength, &infoLog[0]);

            std::cerr << "Shader link failure: " << infoLog.data() << '\n';
            assert(false);
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

            // Don't really need this to be an std::vector, just an array allocated at runtime
            // and then deleted when the scope is exited
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(shader);

            std::cerr << "Shader compliation failure: " << infoLog.data() << '\n';
            assert(false);
            return Result<GLuint, ShaderError>::error(ShaderError::COMPILATION_FAILED);
        }
        return Result<GLuint, ShaderError>::valid(shader);
    }
}
