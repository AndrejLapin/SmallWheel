#include "swpch.hpp"
#include "Camera.hpp"

#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

namespace swheel {
    Camera Camera::CreatePerspective(glm::vec3 position, float fieldOfView) {
        return Camera(glm::translate(glm::mat4x4(1.0f), position),
        glm::perspective(glm::radians(fieldOfView), 1.0f, 0.1f, 10.0f));
    }

    Camera::Camera(glm::mat4x4 transformMatrix, glm::mat4x4 projectionMatrix):
        m_transformMatrix(transformMatrix), m_projectionMatrix(projectionMatrix) {
    }
}
