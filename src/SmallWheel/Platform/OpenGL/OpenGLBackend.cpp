#include "swpch.hpp"
#include "OpenGLBackend.hpp"

#include "glad/gl.h"

namespace swheel {
    void GLClearError() {
        uint32_t errorsCleared = 0;
        while (glGetError() != GL_NO_ERROR && ++errorsCleared < 1000);
    }

    bool GLLogCall(const char* function, const char* file, int line) {
        while (GLenum error = glGetError()) {
            std::cerr << "OpenGL Error: (" << error << ") " << function << ' ' << file << ':' << line << '\n';
            return false;
        }
        return true;
    }

    void OpenGLBackend::Clear() const {
        GLCall(glClearColor(0.2f, 0.3f, 0.5f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    OpenGLBackend::OpenGLBackend(): GraphicsBackend(RendererAPI::OpenGL) {
        // InitGlad();
    }

    OpenGLBackend::~OpenGLBackend() {}
}