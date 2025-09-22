#pragma once
#include "quad.h"
#include "shader.h"

class Player
{
    public:
        Quad skin;
        glm::vec2 vel;
        float gravity = 9.81f;
        bool onGround = false;

        Player(Quad s);

        AABB getAABB();

        void update(GLFWwindow* window, float velocity, Quad tile, float dT);
        void draw(Shader shader);
};