#include "SmallWheel/Renderer/Renderer.hpp"
#include "swpch.hpp"
#include "Application.hpp"
#include "glad/gl.h"

#include "Event.hpp"
#include "Platform/OpenGL/OpenGLWindow.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Shader.hpp"
#include "Window.hpp"

#include "Platform/OpenGL/OpenGLRenderer.hpp"
#include "SmallWheel/Layering/ImguiLayer.hpp"

namespace swheel {

    Application::Application(const std::string& title, int width, int height) {
        // TODO: move to renderer if we even need this
        // SDL_GL_LoadLibrary(nullptr);
        // std::cout << "SDL application created\n";

        // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        // SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

        // Nicer way to create Window (same like it was with renderer)
        m_window = std::make_unique<OpenGLWindow>(title, width, height);
        Renderer& renderer = m_window->GetRenderer();
        // TODO: move to renderer, to init function or something
        InitGlad();

        {
            auto imguiLayer = std::make_unique<ImguiLayer>();
            m_window->PushOverlay(std::move(imguiLayer));
        }

        GLCall(glGenVertexArrays(1, &m_vertexArray));
        GLCall(glBindVertexArray(m_vertexArray));

        float vertices[3 * 3] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
        };

        m_vertexBuffer = renderer.CreateVertexBuffer(vertices, sizeof(vertices));

        GLCall(glEnableVertexAttribArray(0));
        GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr));

        unsigned int indecies[3] = { 0, 1, 2 };
        m_indexBuffer = renderer.CreateIndexBuffer(indecies, sizeof(indecies));

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
                o_Color = vec4(v_Position, 1.0);
            }
        )";

        m_shader = renderer.CreateShader(vertexSrc, fragmentSrc);
    }

    Application::~Application() {
    }

    // Doesn't need to be tied to the application
    void Application::PrintSDLErrors() {
        while (auto error = SDL_GetError()) {
            std::cerr << error << '\n';
        }
    }

    void Application::Run() {
        Event event;
        Renderer& renderer = m_window->GetRenderer();
        do {
            renderer.Clear();

            GLCall(glBindVertexArray(m_vertexArray));
            m_shader->Bind();
            GLCall(glDrawElements(GL_TRIANGLES, m_indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
            m_window->OnUpdate();

            while(event.PollNextEvent()) {
                m_window->OnEvent(event);
            }
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
