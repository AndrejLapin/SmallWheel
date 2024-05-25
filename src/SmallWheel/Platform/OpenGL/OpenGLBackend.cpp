#include "swpch.hpp"
#include "OpenGLBackend.hpp"

#include "glad/gl.h"
#include "SDL_video.h"
#include "SmallWheel/SDLLifetime.hpp"

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
        InitGlad();
    }

    OpenGLBackend::~OpenGLBackend() {}

    void OpenGLBackend::InitGlad() {
        int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
        if (version == 0) {
            SDLLifetime::PrintSDLErrors();
            std::cerr << "Failed to initialize OpenGL context :(\n";
            exit(1);
        }
        std::cout << "OpenGL Info:\n";
        std::cout << " Vendor: " << glGetString(GL_VENDOR) << '\n';
        std::cout << " Renderer: " << glGetString(GL_RENDERER) << '\n';
        std::cout << " Version: " << glGetString(GL_VERSION) << '\n';
    }
}
