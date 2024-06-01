#pragma once

#include "SmallWheel/Core.hpp"
#include "SmallWheel/GraphicsBackend/GraphicsBackend.hpp"

#ifdef SW_ENABLE_GRAPHICS_DEBUG
#define GLCall(x) GLClearError();\
    x;\
    SW_ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x
#endif


namespace swheel {
    // these functions should either be renamed or put into a different file that is not going to be included in headers
    // because of the GL in the name, can be named just OpenGLClearError etc.
    void GLClearError();
    bool GLLogCall(const char* function, const char* file, int line);

    class OpenGLBackend : public GraphicsBackend {
    public:
        OpenGLBackend();
        ~OpenGLBackend();

        void Clear() const override;

        std::unique_ptr<Window> CreateWindow(const std::string& title, int width, int height) const override;
    private:
        void InitGlad() const;

    private:
        // should be mutable while CreateWindow is const
        // if CreateWindow would no longer be const, remove mutable
        mutable bool m_gladInitalised = false;
    };
}
