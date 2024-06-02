#pragma once

#include "OpenGLWindow.hpp"
#include "SmallWheel/Application.hpp"
#include "SmallWheel/Imgui/ImguiLayerImpl.h"

namespace swheel {
    class OpenGLImguiLayerImpl : public ImguiLayerImpl {
    public:
        OpenGLImguiLayerImpl(const OpenGLWindow& ownerWindow);
        ~OpenGLImguiLayerImpl();

        void OnUpdate() override;
        void ImguiFrameBegin() override;
        void ImguiFrameEnd() override;
        
    private:
        const OpenGLWindow& m_ownerWindow;
    };
}
