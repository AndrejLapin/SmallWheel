#include <swpch.hpp>
#include "Application.hpp"

#include "Renderer/Shader.hpp"
#include "SDL.h"
#include "SDL_error.h"
#include "SDL_video.h"
#include "Windowing/Window.hpp"
#include "Windowing/OpenGLWindow.hpp"
#include "glad/gl.h"
#include "Event.hpp"

namespace swheel {

    Application::Application(const std::string& title, int width, int height) {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "Failed to initialize SDL.\n";
        } else {
            std::cout << "SDL initialised.\n";
        }
        SDL_GL_LoadLibrary(nullptr);
        std::cout << "SDL application created\n";

        // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        // SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

        m_window = std::make_unique<OpenGLWindow>(title, width, height);

        InitGlad();

        glGenVertexArrays(1, &m_vertexArray);
        glBindVertexArray(m_vertexArray);

        glGenBuffers(1, &m_vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

        float verticies[3 * 3] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        glGenBuffers(1, &m_indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

        unsigned int indecies[3] = { 0, 1, 2 };
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), verticies, GL_STATIC_DRAW);

        std::string vertexSrc = R"(
            #version 460 core

            layout(location = 0) in vec3 a_Position;

            out vec3 v_Position;

            void main() {
                v_Position = a_Position + 0.5;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 460 core

            layout(location = 0) out vec4 o_Color;

            in vec3 v_Position;

            void main() {
                o_Color = vec4(v_Position * 0.5 + 0.5, 1.0);
            }
        )";

        m_shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);
    }

    Application::~Application() {
        SDL_Quit();
    }

    // Doesn't need to be tied to the application
    void Application::PrintSDLErrors() {
        while (auto error = SDL_GetError()) {
            std::cerr << error << '\n';
        }
    }

    void Application::Run() {
        Event event;
        do {
            glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glBindVertexArray(m_vertexArray);
            m_shader->Bind();
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

            while(event.PollNextEvent()) {
                m_window->OnEvent(event);
            }
            m_window->OnUpdate();
        } while (!m_window->IsClosed());
    }

    void Application::InitGlad() {
        int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
        if (version == 0) {
            PrintSDLErrors();
            std::cerr << "Failed to initialize OpenGL context :(\n";
            exit(1);
        }
        std::cout << "OpenGL Info:\n";
        std::cout << " Vendor: " << glGetString(GL_VENDOR) << '\n';
        std::cout << " Renderer: " << glGetString(GL_RENDERER) << '\n';
        std::cout << " Version: " << glGetString(GL_VERSION) << '\n';
    }
}
