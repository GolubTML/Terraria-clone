#pragma once
#include "quad.h"
#include "shader.h"
#include <vector>

enum class Axis { X, Y };

class Player
{
private:
    void collide(Quad& tile, Axis axis);

public:
    Quad skin;
    glm::vec2 vel = glm::vec2(0.f, 0.f);
    float gravity = 9.81f;
    float jumpVelocity = 3.5f;
    bool onGround = false;
    bool ghostMode = false;

    Player(Quad s);

    void update(GLFWwindow* window, float velocity, std::vector<std::vector<Quad>>& world, float& dT);
    void draw(Shader shader);
};