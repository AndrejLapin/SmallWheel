#include "swpch.hpp"
#include "Camera.hpp"

#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

namespace swheel {
    Camera::Camera(glm::mat4x4 transformMatrix, glm::mat4x4 viewMatrix):
        m_transformMatrix(transformMatrix), m_viewMatrix(viewMatrix) {
    }

    PerspectiveCamera::PerspectiveCamera(glm::vec3 position, float fieldOfView): 
        m_camera(glm::translate(glm::mat4x4(1.0f), position),
        glm::perspective(glm::radians(fieldOfView), 1.0f, 0.1f, 10.0f)) {
    }
}
