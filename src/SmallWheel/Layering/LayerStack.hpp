#pragma once

#include "Layer.hpp"
#include "SmallWheel/Utils/RefCounted.hpp"

namespace swheel {
    class LayerStack {
    public:
        LayerStack() = default;
        ~LayerStack() = default;

        void PushLayer(RefCounted<Layer> layer);
        void PushOverlay(RefCounted<Layer> overlay);
        void PopLayer(const Layer& layer);
        void PopOverlay(const Layer& overlay);
    
        std::vector<RefCounted<Layer>>::iterator begin() { return m_layers.begin(); }
        std::vector<RefCounted<Layer>>::iterator end() { return m_layers.end(); }
    private:
        std::vector<RefCounted<Layer>> m_layers;
        uint32_t m_layerInsertIndex = 0;
    };
}