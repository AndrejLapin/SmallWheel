#pragma once

#include "Layer.hpp"

namespace swheel {
    class LayerStack {
    public:
        LayerStack() = default;
        ~LayerStack() = default;

        void PushLayer(std::unique_ptr<Layer> layer);
        void PushOverlay(std::unique_ptr<Layer> overlay);
        void PopLayer(const Layer& layer);
        void PopOverlay(const Layer& overlay);
    
        std::vector<std::unique_ptr<Layer>>::iterator begin() { return m_layers.begin(); }
        std::vector<std::unique_ptr<Layer>>::iterator end() { return m_layers.end(); }
    private:
        std::vector<std::unique_ptr<Layer>> m_layers;
        uint32_t m_layerInsertIndex = 0;
    };
}