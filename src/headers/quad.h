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

    bool solid = false;
    bool visible = false;

    Quad(bool isSolid, bool isVisible);
    Quad(glm::vec2 position = glm::vec2(0.f, 0.f), float scale = 1.f, float rotation = 0.f, float w = 1.f, float h = 1.f, Texture* tex = nullptr, float tileX = 0.f, float tileY = 0.f);

    bool checkCollision(const Quad& another);

    void draw(Shader& shader);

private:
    GLuint VBO, VAO;
};