#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

class Camera
{
public:
    glm::vec2 position;
    glm::vec2 size;

    Camera(float w, float h);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    void move(glm::vec2& target);
};