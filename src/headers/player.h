#pragma once
#include "quad.h"
#include "shader.h"
#include <vector>

class Player
{
    public:
        Quad skin;
        glm::vec2 vel;
        float gravity = 9.81f;
        float jumpVelocity = 5.f;
        bool onGround = false;

        Player(Quad s);

        void update(GLFWwindow* window, float velocity, std::vector<std::vector<Quad>> world, float dT);
        void collideX(std::vector<std::vector<Quad>> world);
        void collideY(std::vector<std::vector<Quad>> world);
        void draw(Shader shader);
};