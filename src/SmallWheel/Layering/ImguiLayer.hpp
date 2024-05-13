#pragma once

#include "Layer.hpp"
#include <cstdint>

namespace swheel {
    class ImguiLayer : public Layer {
    public:
        ImguiLayer();
        ~ImguiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
    private:
        uint32_t m_time = 0.0f;
    };
}
