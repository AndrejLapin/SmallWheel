#include "swpch.hpp"
#include "OpenGLWindow.hpp"

#include "SDL.h"
#include "SDL_video.h"

#include "OpenGLBackend.hpp"
#include "SmallWheel/Event.hpp"
#include "SmallWheel/Layering/Layer.hpp"
#include "SmallWheel/Utils/RefCounted.hpp"
#include "SmallWheel/GraphicsBackend/GraphicsBackend.hpp"

namespace swheel {
    OpenGLWindow::OpenGLWindow(const GraphicsBackend& parentBackend, const std::string& title, int width, int height):
    Window(parentBackend),
    m_title(title), m_width(width), m_height(height) {
        if (!Init()) {
            m_closed = true;
        }
    }

    OpenGLWindow::~OpenGLWindow() {
        SDL_GL_DeleteContext(m_context);
        SDL_DestroyWindow(m_window);
    }

    // Need to just register events and then dispatch them
    // This is too verbous

    // Do I want a map??
    // If we have a map, how do we ensure ordered event propagation?
    void OpenGLWindow::OnEvent(Event& event) {
        switch (event.m_event.type) {
        case SDL_WINDOWEVENT: {
            if (event.m_event.window.windowID != SDL_GetWindowID(m_window)) {
                return;
            }
            switch(event.m_event.window.event) {
            case SDL_WINDOWEVENT_CLOSE: {
                m_closed = true;
                event.m_handled = true;
                break;
            }
            }
            break;
        }
        }

        if (!event.m_handled) {
            for (auto it = m_layerStack.end(); it != m_layerStack.begin();) {
                (*--it)->OnEvent(event);
                if (event.m_handled) {
                    break;
                }
            }
        }
    }

    void OpenGLWindow::OnUpdate() {
        for (auto& layer : m_layerStack) {
            layer->OnUpdate();
        }
        // do stuff with imgui
        // seperate imgui layer when pushing?
        SDL_GL_SwapWindow(m_window);
    }

    bool OpenGLWindow::Init() {
        m_window = SDL_CreateWindow(
            m_title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            m_width, m_height,
            SDL_WINDOW_OPENGL
        );

        if (m_window == nullptr) {
            SW_ERROR_LOG("Failed to create window.");
            return false;
        }

        m_context = SDL_GL_CreateContext(m_window);

        if (m_context == nullptr) {
            SW_ERROR_LOG("OpenGL context not avalibale.");
            return false;
        }

        return true;
    }

    void OpenGLWindow::PushLayer(RefCounted<Layer> layer) {
        m_layerStack.PushLayer(layer);
        layer->OnAttach(this);
    }

    void OpenGLWindow::PushOverlay(RefCounted<Layer> layer) {
        m_layerStack.PushOverlay(layer);
        layer->OnAttach(this);
    }
}
