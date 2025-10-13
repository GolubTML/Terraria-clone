#include "headers/quad.h"

Quad::Quad(bool isSolid, bool isVisible) : solid(isSolid), visible(isVisible)
{
    if (isSolid && isVisible)
    {
        texture = nullptr;
        pos = glm::vec2(0.f, 0.f);
        size = 0.f;
        rot = 0.f;
        width = 0.f;
        height = 0.f;
    }
}

Quad::Quad(glm::vec2 position, float scale, float rotation, float w, float h, Texture* tex, float tileX, float tileY) 
            : pos(position), size(scale), rot(rotation), width(w), height(h), texture(tex), solid(true), visible(true)
{
    float uv[8];

    if (texture != nullptr)
    {
        texture->getUV(tileX, tileY, uv);
    }
    else 
    {
        memset(uv, 0, sizeof(uv));
    }

    float vertices[] = 
    {
        //X            Y            Z      U    V

        -width / 2.f, -height / 2.f, 0.f,  uv[0], uv[1],
        width / 2.f, -height / 2.f , 0.f,  uv[2], uv[3],
        width / 2.f,  height / 2.f , 0.f,  uv[6], uv[7],

        -width / 2.f, -height / 2.f, 0.f,  uv[0], uv[1],
        -width / 2.f , height / 2.f, 0.f,  uv[4], uv[5],
        width / 2.f ,  height / 2.f, 0.f,  uv[6], uv[7],
    };

    if (texture != nullptr)
    {
        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
        // Base
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0); 
        
        // UV
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    else 
    {
        VAO = 0;
        VBO = 0;
    }
}

void Quad::draw(Shader& shader)
{
    if (!visible) return;

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(pos, 0.f));
    model = glm::rotate(model, rot, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(size));

    GLuint modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    if (texture != nullptr)
    {
        glActiveTexture(GL_TEXTURE0);
        texture->bind();

        glUniform1i(glGetUniformLocation(shader.ID, "uTexture"), 0);
        glUniform1i(glGetUniformLocation(shader.ID, "uUseTexture"), true);
    }
    else 
        glUniform1i(glGetUniformLocation(shader.ID, "uUseTexture"), false);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    if (texture != nullptr)
    {
        texture->unbind(); 
    }
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
