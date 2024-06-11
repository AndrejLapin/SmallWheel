#include "swpch.hpp"
#include "OpenGLShader.hpp"

#include "OpenGLBackend.hpp"
#include "SmallWheel/Core.hpp"
#include "SmallWheel/GraphicsBackend/Shader.hpp"
#include "SmallWheel/Utils/FileUtils.hpp"

namespace swheel {
    OpenGLShader::OpenGLShader(const ShaderResourceRegistry::Entry& vertexEntry, const ShaderResourceRegistry::Entry& fragmentEntry):
        m_vertexPath(vertexEntry.GetPath(RendererAPI::OpenGL)), 
        m_fragmentPath(fragmentEntry.GetPath(RendererAPI::OpenGL)) {
    }

    OpenGLShader::~OpenGLShader() {
        Unload();
    }

    Result<GLuint, Shader::ShaderError> OpenGLShader::LoadShader(bool haltProgram) {
        GLuint vertexShader;
        GLuint fragmentShader;
        {
            std::string vertexSource = fileUtils::GetFileContents(m_vertexPath);
            std::string fragmentSource = fileUtils::GetFileContents(m_fragmentPath);

            Result<GLuint, ShaderError> vertexShaderResult = CompileShader(vertexSource, GL_VERTEX_SHADER, haltProgram);
            Result<GLuint, ShaderError> fragmentShaderResult = CompileShader(fragmentSource, GL_FRAGMENT_SHADER, haltProgram);

            if (!vertexShaderResult.isSuccess() || !fragmentShaderResult.isSuccess()) {
                if (vertexShaderResult.isSuccess()) {
                    GLCall(glDeleteShader(vertexShaderResult.getResult()));
                } else if (fragmentShaderResult.isSuccess()) {
                    GLCall(glDeleteShader(fragmentShaderResult.getResult()));
                }
                return Result<GLuint, Shader::ShaderError>::error(Shader::ShaderError::COMPILATION_FAILED);
            }
            vertexShader = vertexShaderResult.getResult();
            fragmentShader = fragmentShaderResult.getResult();
        }
        
        uint32_t programId = glCreateProgram();
        ShaderError error = LinkShaders({vertexShader, fragmentShader}, programId, haltProgram);
        if (error != ShaderError::NONE) {
            GLCall(glDeleteProgram(programId));
            GLCall(glDeleteProgram(vertexShader));
            GLCall(glDeleteProgram(fragmentShader));
            return Result<GLuint, Shader::ShaderError>::error(error);
        }

        // Always detach shaders after a successful link.
        GLCall(glDetachShader(programId, vertexShader));
        GLCall(glDetachShader(programId, fragmentShader));
        GLCall(glDeleteShader(vertexShader));
        GLCall(glDeleteShader(fragmentShader));
        
        return Result<GLuint, Shader::ShaderError>::success(programId);
    }

    Shader::ShaderError OpenGLShader::LinkShaders(const std::vector<GLuint>& shaders, uint32_t program, bool haltProgram) {
        for (auto shader : shaders) {
            GLCall(glAttachShader(program, shader));
        }
        GLCall(glLinkProgram(program));

        GLint isLinked = 0;
        GLCall(glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked));
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            GLCall(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength));

            if (maxLength > 0 ) {
                auto infoLog = std::make_unique<GLchar[]>(maxLength);
                GLCall(glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]));

                SW_ERROR_LOG("Shader link failure: ", infoLog.get());
            } else {
                SW_ERROR_LOG("Unknown shader link failure!");
            }
            SW_ASSERT(!haltProgram);
            return ShaderError::LINKING_FAILED;
        }
        return ShaderError::NONE;
    }

    Result<GLuint, Shader::ShaderError> OpenGLShader::CompileShader(const std::string& shaderSource, GLenum type, bool haltProgram) {
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

                SW_ERROR_LOG("Shader compliation failure: ", infoLog.get());
            } else {
                SW_ERROR_LOG("Unknown shader compilation failure!");
            }
            SW_ASSERT(!haltProgram);
            return Result<GLuint, ShaderError>::error(ShaderError::COMPILATION_FAILED);
        }
        return Result<GLuint, ShaderError>::success(shader);
    }

    void OpenGLShader::Load() {
        Result<GLuint, Shader::ShaderError> result = LoadShader();
        if (result.isSuccess()) {
            m_programId = result.getResult();
        }
    }

    void OpenGLShader::Unload() {
        GLCall(glDeleteProgram(m_programId));
    }

    void OpenGLShader::Reload() {
        // we should detect what change occured to which shader
        // and only reload that source
        // maybe also check if the file still exists, if it doesn't don't reload it
        Unload();
        Load();
    }

    void OpenGLShader::TryReload() {
        Result<GLuint, Shader::ShaderError> result = LoadShader(false);
        if (!result.isSuccess()) {
            return;
        }
        Unload();
        m_programId = result.getResult();
    }

    void OpenGLShader::Bind() const {
        GLCall(glUseProgram(m_programId));
    }

    void OpenGLShader::Unbind() const {
        if (m_programId) {
            GLCall(glUseProgram(m_programId));
        }
    }
}
