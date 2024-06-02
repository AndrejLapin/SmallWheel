#pragma once

namespace swheel {
    class ImguiLayerImpl {
    public:
        virtual ~ImguiLayerImpl() {}

        virtual void OnUpdate() = 0; // might be redundant
        virtual void ImguiFrameBegin() = 0;
        virtual void ImguiFrameEnd() = 0;
    };
}
