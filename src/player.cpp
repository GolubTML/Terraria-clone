#include "headers/player.h"
#include <cmath>

Player::Player(Quad s) : skin(s) 
{ 
    pos = skin.pos;
}

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

        pos.x += vel.x;

        int playerTileY = static_cast<int>(pos.y / 16.f);
        int playerTileX = static_cast<int>(pos.x / 16.f);
        
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
        pos.y += vel.y;

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
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) pos.x -= speed / 10.f;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) pos.x += speed / 10.f;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) pos.y += speed / 10.f;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) pos.y -= speed / 10.f;
    }

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    int tileX = static_cast<int>(mouseX) / 16;
    int tileY = static_cast<int>(mouseY) / 16;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
    {
        if (tileY >= 0 && tileY < world.size() && tileX >= 0 && tileX < world[0].size())
        {
            Quad& quad = world[tileY][tileX];
            if (quad.solid && quad.visible)
            {
                quad.solid   = false;
                quad.visible = false;
            }
        }
    }

    skin.pos = pos;
}

bool Player::isColliding(const Quad& another)
{
    float leftA   = pos.x - skin.width  / 2.0f;
    float rightA  = pos.x + skin.width  / 2.0f;
    float bottomA = pos.y - skin.height / 2.0f;
    float topA    = pos.y + skin.height / 2.0f;

    float leftB   = another.pos.x - another.width  / 2.0f;
    float rightB  = another.pos.x + another.width  / 2.0f;
    float bottomB = another.pos.y - another.height / 2.0f;
    float topB    = another.pos.y + another.height / 2.0f;

    return leftA < rightB && rightA > leftB &&
           bottomA < topB && topA > bottomB;
}

void Player::collide(Quad& tile, Axis axis)
{
    if (isColliding(tile)) 
    {
        if (axis == Axis::X)
        {
            float leftA   = pos.x - skin.width  / 2.0f;
            float rightA  = pos.x + skin.width  / 2.0f;
            float leftB   = tile.pos.x - tile.width  / 2.0f;
            float rightB  = tile.pos.x + tile.width  / 2.0f;

            float overlapLeft  = rightB - leftA;
            float overlapRight = rightA - leftB;

            if (overlapLeft < overlapRight)
                pos.x = rightB + skin.width / 2.0f;
            else
                pos.x = leftB - skin.width / 2.0f;

            vel.x = 0.0f;
        }
        else
        {
            float bottomA = pos.y - skin.height / 2.0f;
            float topA    = pos.y + skin.height / 2.0f;
            float bottomB = tile.pos.y - tile.height / 2.0f;
            float topB    = tile.pos.y + tile.height / 2.0f;

            float overlapBottom = topB - bottomA;
            float overlapTop    = topA - bottomB;

            if (overlapBottom < overlapTop) 
            {
                pos.y = topB + skin.height / 2.0f;
                onGround = true;
            }
            else
            {
                pos.y = bottomB - skin.height / 2.0f;
            }

            vel.y = 0.0f;
        }
    }
}

void Player::draw(Shader shader)
{
    skin.draw(shader);
}