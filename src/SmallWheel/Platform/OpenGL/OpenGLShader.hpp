#pragma once

#include "glad/gl.h"
#include "SmallWheel/GraphicsBackend/Shader.hpp"
#include "SmallWheel/Utils/Result.hpp"

namespace swheel {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
        ~OpenGLShader();

        void Load() override;
        void Unload() override;
        void Reload() override;
        void TryReload() override;
        void Bind() const override;
        void Unbind() const override;

    private:
        Result<GLuint, ShaderError> LoadShader(bool haltProgram = true);
        ShaderError LinkShaders(const std::vector<GLuint>& shaders, GLuint program, bool haltProgram);
        Result<GLuint, ShaderError> CompileShader(const std::string& shaderSource, GLenum type, bool haltProgram);

    private:
        std::filesystem::path m_vertexPath, m_fragmentPath;
        GLuint m_programId = 0;
    };
}
