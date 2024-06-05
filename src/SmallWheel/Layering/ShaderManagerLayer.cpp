#include "SDL_scancode.h"
#include "swpch.hpp"
#include "ShaderManagerLayer.hpp"

#include "SDL_events.h"
#include <iostream>

namespace swheel {
    ShaderManagerLayer::ShaderManagerLayer(const std::string& name): Layer(name) {
        m_shaders.reserve(1);
    }

    void ShaderManagerLayer::OnEvent(Event& event) {
        if (event.m_event.type == SDL_KEYUP) {
            if (event.m_event.key.keysym.scancode == SDL_SCANCODE_NONUSBACKSLASH) { // need to make sure this is actually the '~' key
                ReloadAllShaders();
                std::cout << "Shaders reloaded\n";
            }
        }
    }

    void ShaderManagerLayer::AddShader(RefCounted<Shader> shader) {
        if (m_shaders.size() == m_shaders.capacity()) {
            m_shaders.reserve(std::ceil(m_shaders.size() * 1.5f));
        }
        m_shaders.emplace_back(shader);
    }

    void ShaderManagerLayer::RemoveShader(RefCounted<Shader> shader) {
        auto it = m_shaders.begin();
        for (; it != m_shaders.end(); ++it) {
            if (*it == shader) {
                m_shaders.erase(it);
            }
        }
    }

    void ShaderManagerLayer::ReloadAllShaders() {
        for (auto& shader : m_shaders) {
            shader->Reload();
        }
    }
}