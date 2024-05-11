#pragma once

#include "SmallWheel/Core.hpp"
#include "SmallWheel/Renderer/Renderer.hpp"

#define GLCall(x) GLClearError();\
    x;\
    SW_ASSERT(GLLogCall(#x, __FILE__, __LINE__))


namespace swheel {
    // these functions should either be renamed or put into a different file that is not going to be included in headers
    // because of the GL in the name, can be named just OpenGLClearError etc.
    void GLClearError();
    bool GLLogCall(const char* function, const char* file, int line);

    class OpenGLRenderer : public Renderer {
    public:
        OpenGLRenderer();
        ~OpenGLRenderer();

        void Clear() const override;
        void Draw(const VertexBuffer& va, const IndexBuffer& ib, const Shader& shader) const override;
    };
}
