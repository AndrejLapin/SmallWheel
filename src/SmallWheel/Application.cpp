#include "swpch.hpp"
#include "Application.hpp"

#include "glad/gl.h"
#include "Event.hpp"
#include "Window.hpp"
#include "Platform/OpenGL/OpenGLWindow.hpp"
#include "Imgui/ImguiLayer.hpp"
#include "GraphicsBackend/Shader.hpp"
#include "GraphicsBackend/GraphicsBackend.hpp"
#include "GraphicsBackend/VertexLayout.hpp"
#include "GraphicsBackend/CommonVertexLayouts.hpp"
#include "GraphicsBackend/Renderers/SimpleMeshRenderer.hpp"
#include "GraphicsBackend/Mesh.hpp"
#include "GraphicsBackend/MeshData.hpp"
#include "GraphicsBackend/ShaderRegistry.hpp"

namespace swheel {

    Application::Application(const std::string& title, int width, int height) {
        m_sdlLifetime.Init();
        // TODO: move to renderer if we even need this
        // SDL_GL_LoadLibrary(nullptr);
        // std::cout << "SDL application created\n";

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        // Nicer way to create Window (same like it was with renderer)
        m_window = std::make_unique<OpenGLWindow>(title, width, height);

        const GraphicsBackend& graphicsBackend = m_window->GetGraphicsBackend();
        m_window->PushOverlay<ImguiLayer>(m_sharedData, "Imgui");

        std::string vertexSrc = R"(
            #version 410 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            out vec3 v_Position;
            out vec4 v_Color;

            void main() {
                v_Position = a_Position + 0.5;
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 410 core

            layout(location = 0) out vec4 o_Color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main() {
                o_Color = v_Color;
            }
        )";
        m_shader = graphicsBackend.CreateShader(shaderRegistry::s_colorOutVertexShader, shaderRegistry::s_colorInFragmentShader);
        m_shader->Load();
    }

    Application::~Application() {
    }

    void Application::Run() {
        Event event;
        const GraphicsBackend& graphicsBackend = m_window->GetGraphicsBackend();

        float vertices[3 * 7] = {
            -0.8f,  -0.5f, 0.0f,     1.0f, 0.0f, 0.0f, 1.0f,
            0.2f,  -0.5f, 0.0f,      0.0f, 1.0f, 0.0f, 1.0f,
            -0.3f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f, 
        };
        unsigned int indecies[3] = { 0, 1, 2 };
        MeshData meshData(commonLayouts::PositionColor::Layout(), vertices, 3, indecies, 3);
        m_sharedData.meshData = &meshData;
        std::unique_ptr<Mesh> mesh = graphicsBackend.CreateMeshInstance(meshData);
        mesh->Load();

        do {
            graphicsBackend.Clear();
            mesh->Reload();
            graphicsBackend.GetSimpleRenderer().DrawMesh(*m_shader, *mesh);
            m_window->OnUpdate();

            while(event.PollNextEvent()) {
                m_window->OnEvent(event);
            }
        } while (!m_window->IsClosed());
    }
}
