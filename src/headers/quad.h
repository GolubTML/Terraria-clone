#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "shader.h"

struct AABB
{
    glm::vec2 pos;
    glm::vec2 center;
};

class Quad
{
public:
    GLuint VBO, VAO;
    glm::vec2 pos;
    float size;
    float rot;
    float width;
    float height;

    Quad(glm::vec2 position, float scale, float rotation, float w, float h);

    bool checkCollision(const AABB& a, const AABB& b);

    void draw(Shader& shader);
};