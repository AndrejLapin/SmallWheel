#pragma once

#include "OpenGLWindow.hpp"
#include "SmallWheel/Imgui/ImguiLayerImpl.h"

namespace swheel {
    class OpenGLImguiLayerImpl : public ImguiLayerImpl {
    public:
        OpenGLImguiLayerImpl(const OpenGLWindow& ownerWindow);

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void ImguiFrameBegin() override;
        void ImguiFrameEnd() override;
        
    private:
        const OpenGLWindow& m_ownerWindow;
    };
}
