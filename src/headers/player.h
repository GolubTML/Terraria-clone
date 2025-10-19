#pragma once
#include "quad.h"
#include "shader.h"
#include <vector>

enum class Axis { X, Y };

class Textrue;

struct BodyPart
{
    Texture* texture = nullptr;
    Quad quad;
    
    glm::vec2 offset = glm::vec2(0.f, 0.f);
    glm::vec2 size = glm::vec2(0.f, 0.f);

    BodyPart();

    void draw(Shader& shader, const glm::vec2& playerPos);
};

class PlayerRenderer
{
public:
    BodyPart head, eye1, eye2, body, leftHand, rightHand, legs;

    void init();
    void draw();
};

class Player
{
private:
    bool isColliding(const Quad& another);
    void collide(Quad& tile, Axis axis);

public:
    Quad skin;

    glm::vec2 pos = glm::vec2(0.f, 0.f);
    glm::vec2 vel = glm::vec2(0.f, 0.f);

    float gravity = 9.81f;
    float jumpVelocity = 3.5f;
    bool onGround = false;
    bool ghostMode = false;

    Player(Quad s);

    void update(GLFWwindow* window, float velocity, std::vector<std::vector<Quad>>& world, float& dT);
    void draw(Shader shader);
};