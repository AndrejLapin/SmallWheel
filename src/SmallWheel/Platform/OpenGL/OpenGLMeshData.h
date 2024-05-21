#pragma once

#include "glad/gl.h"

namespace swheel {
    struct OpenGLMeshData {
        GLuint vartexArray  = 0;
        GLuint vertexBuffer = 0;
        GLuint IndexBuffer  = 0;
    };
}
