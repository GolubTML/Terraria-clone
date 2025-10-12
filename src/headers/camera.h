#pragma once
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
    float zoom = 1.f;

    Camera(float w, float h);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    void move(glm::vec2 target);
    void setZoom(float& factor);
    void draw(std::vector<std::vector<Quad>>& world, Shader& shader);
};