#include "headers/player.h"
#include <cmath>

Player::Player(Quad s) : skin(s) { }

void Player::update(GLFWwindow* window, float speed, std::vector<std::vector<Quad>>& world, float& dT)
{
    if (!ghostMode)
    {
        int radius = 5;
        
        vel.x = 0.f;

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) vel.x -= speed * dT;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) vel.x += speed * dT;

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

        skin.pos.x += vel.x;
        
        int playerTileY = static_cast<int>(skin.pos.y / 16.f);
        int playerTileX = static_cast<int>(skin.pos.x / 16.f);
        
        int worldH = static_cast<int>(world.size());     
        int worldW = static_cast<int>(world[0].size());  
        
        int startX = std::max(playerTileX - radius, 0);
        int endX   = std::min(playerTileX + radius, worldW - 1);
        
        int startY = std::max(playerTileY - radius, 0);
        int endY   = std::min(playerTileY + radius, worldH - 1);
        
        for (int y = startY; y <= endY; ++y)
        {
            for (int x = startX; x <= endX; ++x)
            {
                collide(world[y][x], Axis::X);
            }
        }
        
        onGround = false;
        skin.pos.y += vel.y;

        for (int y = startY; y <= endY; ++y)
        {
            for (int x = startX; x <= endX; ++x)
            {
                collide(world[y][x], Axis::Y);
            }
        }
    }
    else
    {
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) skin.pos.x -= speed / 10.f;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) skin.pos.x += speed / 10.f;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) skin.pos.y += speed / 10.f;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) skin.pos.y -= speed / 10.f;
    }
}

void Player::collide(Quad& tile, Axis axis)
{
    if (skin.checkCollision(tile)) 
    {
        if (axis == Axis::X)
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
        else
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

void Player::draw(Shader shader)
{
    skin.draw(shader);
}