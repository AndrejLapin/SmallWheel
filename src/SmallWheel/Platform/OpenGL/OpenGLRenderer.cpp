#include "swpch.hpp"
#include "OpenGLRenderer.hpp"

#include "glad/gl.h"

namespace swheel {
    void OpenGLRenderer::Clear() const {
        // Add GL error handling
        glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    OpenGLRenderer::OpenGLRenderer(): Renderer(RendererAPI::OpenGL) {}

    OpenGLRenderer::~OpenGLRenderer() {}
}
