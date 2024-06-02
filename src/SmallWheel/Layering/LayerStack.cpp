#include "swpch.hpp"
#include "LayerStack.hpp"

namespace swheel {
    void LayerStack::PushLayer(RefCounted<Layer> layer) {
        m_layers.emplace(m_layers.begin() + m_layerInsertIndex, std::move(layer));
        ++m_layerInsertIndex;
    }

    void LayerStack::PushOverlay(RefCounted<Layer> overlay) {
        m_layers.emplace_back(std::move(overlay));
    }

    void LayerStack::PopLayer(const Layer& layer) {
        assert(false); // Not implemented
    }

    void LayerStack::PopOverlay(const Layer& overlay) {
        assert(false); // Not implemented
    }
}