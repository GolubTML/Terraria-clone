#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include <vector>

#include "quad.h"

class Camera
{
public:
    glm::vec2 position;
    glm::vec2 size;

    Camera(float w, float h);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    void move(glm::vec2 target);
    void draw(std::vector<std::vector<Quad>>& world, Shader& shader);
};