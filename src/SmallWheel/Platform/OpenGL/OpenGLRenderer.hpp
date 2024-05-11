#pragma once

#include "SmallWheel/Renderer/Renderer.hpp"

namespace swheel {
    class OpenGLRenderer : public Renderer {
    public:
        OpenGLRenderer();
        ~OpenGLRenderer();

        void Clear() const override;
        // void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const override;
    };
}
