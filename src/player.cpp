#include "headers/player.h"

Player::Player(Quad s) : skin(s) { }

void Player::update(GLFWwindow* window, float speed, std::vector<std::vector<Quad>> world, float dT)
{
    vel.x = 0;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) vel.x -= speed * dT;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) vel.x += speed * dT;

    skin.pos.x += vel.x;
    collideX(world);

    skin.pos.y += vel.y;
    collideY(world);

    if (!onGround)
    {
        vel.y -= gravity * dT;
    }
    else 
    {
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            vel.y = jumpVelocity;
            onGround = false;     
        }
        
        vel.y = vel.y;
    }
}

void Player::collideX(std::vector<std::vector<Quad>> world)
{
    for (auto& row : world)
    {
        for (auto& tile : row)
        {
            if (skin.checkCollision(tile)) 
            {
                float leftA   = skin.pos.x - skin.width  / 2.0f;
                float rightA  = skin.pos.x + skin.width  / 2.0f;
                float leftB   = tile.pos.x - tile.width  / 2.0f;
                float rightB  = tile.pos.x + tile.width  / 2.0f;

                float overlapLeft  = rightB - leftA;
                float overlapRight = rightA - leftB;

                if (overlapLeft < overlapRight)
                    skin.pos.x = rightB + skin.width / 2.0f;
                else
                    skin.pos.x = leftB - skin.width / 2.0f;

                vel.x = 0.0f;
            }
        }
    }
}

void Player::collideY(std::vector<std::vector<Quad>> world)
{
    onGround = false;

    for (auto& row : world)
    {
        for (auto& tile : row)
        {
            if (skin.checkCollision(tile))
            {
                float bottomA = skin.pos.y - skin.height / 2.0f;
                float topA    = skin.pos.y + skin.height / 2.0f;
                float bottomB = tile.pos.y - tile.height / 2.0f;
                float topB    = tile.pos.y + tile.height / 2.0f;

                float overlapBottom = topB - bottomA;
                float overlapTop    = topA - bottomB;

                if (overlapBottom < overlapTop) 
                {
                    skin.pos.y = topB + skin.height / 2.0f;
                    onGround = true;
                }
                else
                {
                    skin.pos.y = bottomB - skin.height / 2.0f;
                }

                vel.y = 0.0f;
            }
        }
    }
}


void Player::draw(Shader shader)
{
    skin.draw(shader);
}