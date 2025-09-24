#include "headers/quad.h"

Quad::Quad(glm::vec2 position = glm::vec2(0.f, 0.f),  float scale = 1.f, float rotation = 0.f, float w = 1.f, float h = 1.f) 
            : pos(position), size(scale), rot(rotation), width(w), height(h)
{
    float vertices[] = 
    {
        //X    Y      Z

        -width / 2.f, -height / 2.f, 0.f,
        width / 2.f, -height / 2.f, 0.f,
        width / 2.f,  height / 2.f, 0.f,

        -width / 2.f, -height / 2.f, 0.f,
        -width / 2.f , height / 2.f, 0.f,
        width / 2.f ,  height / 2.f, 0.f,
    };

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  
}

void Quad::draw(Shader& shader)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(pos, 0.f));
    model = glm::rotate(model, rot, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(size));

    GLuint modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

bool Quad::checkCollision(const Quad& another)
{
    float leftA   = pos.x - width  / 2.0f;
    float rightA  = pos.x + width  / 2.0f;
    float bottomA = pos.y - height / 2.0f;
    float topA    = pos.y + height / 2.0f;

    float leftB   = another.pos.x - another.width  / 2.0f;
    float rightB  = another.pos.x + another.width  / 2.0f;
    float bottomB = another.pos.y - another.height / 2.0f;
    float topB    = another.pos.y + another.height / 2.0f;

    return leftA < rightB && rightA > leftB &&
           bottomA < topB && topA > bottomB;
}
