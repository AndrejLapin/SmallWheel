#pragma once

#include "glm/glm.hpp"

namespace swheel {
    class Camera {
    public:
        static Camera CreatePerspective(glm::vec3 position, float fieldOfView);

        Camera(glm::mat4x4 transformMatrix, glm::mat4x4 projectionMatrix);

        const glm::mat4x4& GetTransform() const { return m_transformMatrix; }
        const glm::mat4x4& GetProjectionMatrix() const { return m_projectionMatrix;}

    private:
        glm::mat4x4 m_transformMatrix;
        glm::mat4x4 m_projectionMatrix;
    };
}
