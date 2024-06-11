#include "swpch.hpp"
#include "OpenGLBackend.hpp"

#include "glad/gl.h"
#include "SDL_video.h"
#include "SmallWheel/SDLLifetime.hpp"
#include "SmallWheel/Window.hpp"

namespace swheel {
    void GLClearError() {
        uint32_t errorsCleared = 0;
        while (glGetError() != GL_NO_ERROR && ++errorsCleared < 1000);
    }

    bool GLLogCall(const char* function, const char* file, int line) {
        while (GLenum error = glGetError()) {
            SW_ERROR_LOG("OpenGL Error: (", error, ") ", function, ' ', file, ':', line);
            return false;
        }
        return true;
    }

    OpenGLBackend::OpenGLBackend(): GraphicsBackend(RendererAPI::OpenGL) {
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    }

    OpenGLBackend::~OpenGLBackend() {}

    void OpenGLBackend::Clear() const {
        GLCall(glClearColor(0.2f, 0.3f, 0.5f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    std::unique_ptr<Window> OpenGLBackend::CreateWindow(const std::string& title, int width, int height) const {
        std::unique_ptr<Window> window = GraphicsBackend::CreateWindow(title, width, height);
        if(!m_gladInitalised) {
            InitGlad();
            m_gladInitalised = true;
        }
        return window;
    }

    void OpenGLBackend::InitGlad() const {
        int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
        if (version == 0) {
            SDLLifetime::PrintSDLErrors();
            SW_ERROR_LOG("Failed to initialize OpenGL context :(");
            exit(1);
        }
        SW_LOG("OpenGL Info:");
        SW_LOG(" Vendor: ", glGetString(GL_VENDOR));
        SW_LOG(" Renderer: ", glGetString(GL_RENDERER));
        SW_LOG(" Version: ", glGetString(GL_VERSION));
    }
}
