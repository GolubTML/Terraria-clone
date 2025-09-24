#include "headers/player.h"

Player::Player(Quad s) : skin(s) { }

void Player::update(GLFWwindow* window, float speed, Quad tile, float dT)
{
    vel.x = 0;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) vel.x -= speed * dT;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) vel.x += speed * dT;

    skin.pos.x += vel.x;

    if (skin.checkCollision(tile))
    {
        onGround = true;
        vel.y = 0.0f;
        skin.pos.y = tile.pos.y + (tile.height / 2.0f) + (skin.height / 2.0f);
    }
    else
    {
        onGround = false;
    }

    if (skin.checkCollision(tile)) 
    {
        float leftA   = skin.pos.x - skin.width  / 2.0f;
        float rightA  = skin.pos.x + skin.width  / 2.0f;
        float bottomA = skin.pos.y - skin.height / 2.0f;
        float topA    = skin.pos.y + skin.height / 2.0f;

        float leftB   = tile.pos.x - tile.width  / 2.0f;
        float rightB  = tile.pos.x + tile.width  / 2.0f;
        float bottomB = tile.pos.y - tile.height / 2.0f;
        float topB    = tile.pos.y + tile.height / 2.0f;

        float overlapX1 = rightB - leftA;   
        float overlapX2 = rightA - leftB; 

        if (overlapX1 < overlapX2) 
        {
            skin.pos.x = rightB + skin.width / 2.0f;
        } 
        else 
        {
            skin.pos.x = leftB - skin.width / 2.0f;
        }

        vel.x = 0.0f;
    }


    skin.pos.y += vel.y;

    if (!onGround)
    {
        vel.y -= gravity * dT;
    }
    else 
    {
        vel.y = vel.y;
    }
}

void Player::draw(Shader shader)
{
    skin.draw(shader);
}