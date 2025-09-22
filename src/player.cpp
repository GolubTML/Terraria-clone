#include "headers/player.h"

Player::Player(Quad s) : skin(s) { }

AABB Player::getAABB()
{
    return { skin.pos, glm::vec2(skin.width / 2.f, skin.height / 2.f) };
}

void Player::update(GLFWwindow* window, float speed, Quad tile, float dT)
{
    vel.x = 0;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) vel.x -= speed * dT;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) vel.x += speed * dT;

    if (tile.checkCollision(getAABB(), { tile.pos, glm::vec2(tile.width / 2.f, tile.height / 2.f) }))
    {
        onGround = true;
        vel.y = 0.0f;
        skin.pos.y = tile.pos.y + (tile.height / 2.0f) + (skin.height / 2.0f);
    }
    else
    {
        onGround = false;
    }

    if (!onGround)
    {
        vel.y -= gravity * dT;
    }
    else 
    {
        vel.y = vel.y;
    }

    skin.pos.x += vel.x;
    skin.pos.y += vel.y;
}

void Player::draw(Shader shader)
{
    skin.draw(shader);
}