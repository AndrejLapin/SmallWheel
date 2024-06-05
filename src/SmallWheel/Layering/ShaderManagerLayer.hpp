#pragma once

#include "Layer.hpp"
#include "SmallWheel/Utils/RefCounted.hpp"

namespace swheel {
    class Shader;

    class ShaderManagerLayer : public Layer {
    public:
        ShaderManagerLayer(const std::string& name = "ShaderManager");

        void OnEvent(Event& event) override;

        void AddShader(RefCounted<Shader> shader);
        void RemoveShader(RefCounted<Shader> shader);

    private:
        void ReloadAllShaders();

    private:
        std::vector<RefCounted<Shader>> m_shaders;
    };
}
