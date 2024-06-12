#pragma once

#include "glm/glm.hpp"

namespace swheel {
    class Camera {
    public:
        Camera(glm::mat4x4 transformMatrix, glm::mat4x4 viewMatrix);

        const glm::mat4x4& GetTransform() const { return m_transformMatrix; }
        const glm::mat4x4& GetViewMatrix() const { return m_viewMatrix;}

    private:
        glm::mat4x4 m_transformMatrix;
        glm::mat4x4 m_viewMatrix;
    };

    class PerspectiveCamera {
    public:
        PerspectiveCamera(glm::vec3 position, float fieldOfView);
        Camera& GetCamera() { return m_camera; }
    private:
        Camera m_camera;
    };
}
