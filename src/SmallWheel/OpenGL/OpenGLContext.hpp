#pragma once

// Maybe this is not needed yet

namespace swheel {
    class OpenGLWindow;

    class OpenGLContext {
    public:
        OpenGLContext(OpenGLWindow* window);

        void Init();
        void SwapBuffers();
    };
}
