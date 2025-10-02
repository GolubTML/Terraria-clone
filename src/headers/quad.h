#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "shader.h"
#include "texture.h"

class Quad
{
public:
    Texture* texture;
    glm::vec2 pos;
    float size;
    float rot;
    float width, height;
    float tileX, tileY;

    Quad(glm::vec2 position, float scale, float rotation, float w, float h, Texture* tex);

    bool checkCollision(const Quad& another);

    void draw(Shader& shader);

private:
    GLuint VBO, VAO;
};