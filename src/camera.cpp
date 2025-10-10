#include "headers/camera.h"
#include "imgui/imgui.h"
#include <cmath>
#include <iostream>

Camera::Camera(float w, float h) : position(0.f), size(w, h) { }

glm::mat4 Camera::getViewMatrix() const
{
    return glm::translate(glm::mat4(1.f), glm::vec3(-position, 0.f));
}

glm::mat4 Camera::getProjectionMatrix() const
{
    return glm::ortho(0.f, size.x, 0.f, size.y, -1.f, 1.f);
}

void Camera::move(glm::vec2 target)
{
    position = target;
}

void Camera::draw(std::vector<std::vector<Quad>>& world, Shader& shader)
{
    const float TILE_SIZE = 16.f;

    if (world.empty()) return;

    int height = (int)world.size();
    int width = (int)world[0].size();

    float left = position.x;
    float right = position.x + size.x;
    float bottom = position.y;
    float top = position.y + size.y;

    int x0 = std::max(0, (int)std::floor(left / TILE_SIZE) - 1);
    int x1 = std::min(width - 1, (int)std::ceil(right / TILE_SIZE) + 1);
    int y0 = std::max(0, (int)std::floor(bottom / TILE_SIZE) - 1);
    int y1 = std::min(height, (int)std::ceil(top / TILE_SIZE));

    std::cout << "tiles: X(" << x0 << "-" << x1 << ") Y(" << y0 << "-" << y1 << ")\n";

    for (int y = y0; y <= y1; ++y)
    {
        if (y < 0 || y >= height) continue;

        int rowSize = (int)world[y].size();
        if (rowSize == 0) return;

        int startX = std::max(x0, 0);
        int endX   = std::min(x1, rowSize - 1);

        for (int x = startX; x <= endX; ++x)
        {
            //if (x < 0 || x >= rowSize) continue;
            world[y][x].draw(shader);
        }
    }
} 