#include "headers/camera.h"

Camera::Camera(float w, float h) : position(0.f), size(w, h) { }

glm::mat4 Camera::getViewMatrix() const
{
    return glm::translate(glm::mat4(1.f), glm::vec3(-position, 0.f));
}

glm::mat4 Camera::getProjectionMatrix() const
{
    return glm::ortho(0.f, size.x, 0.f, size.y, -1.f, 1.f);
}

void Camera::move(glm::vec2 target)
{
    position = target;
}