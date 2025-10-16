#include "headers/camera.h"
#include "imgui/imgui.h"
#include <cmath>
#include <iostream>

Camera::Camera(float w, float h) : position(0.f), size(w, h) { }

glm::mat4 Camera::getViewMatrix() const
{
    return glm::translate(glm::mat4(1.f), glm::vec3(-position.x, -position.y, 0.f));
}

glm::mat4 Camera::getProjectionMatrix() const
{
    float viewW = size.x / zoom;
    float viewH = size.y / zoom;

    float halfW = viewW / 2.f;
    float halfH = viewH / 2.f;

    return glm::ortho(-halfW, halfW, -halfH, halfH, -1.f, 1.f);
}

void Camera::setZoom(float& factor)
{
    zoom = factor;
}

void Camera::move(glm::vec2 target)
{
    position = target;
}

void Camera::draw(std::vector<std::vector<Quad>>& world, Shader& shader)
{
    const float TILE_SIZE = 16.f;

    if (world.empty()) return;

    int height = static_cast<int>(world.size());
    int width = static_cast<int>(world[0].size());

    float left   = position.x - size.x / 2.f;
    float right  = position.x + size.x / 2.f;
    float bottom = position.y - size.y / 2.f;
    float top    = position.y + size.y / 2.f;

    int x0 = std::max(0, static_cast<int>(std::floor(left / TILE_SIZE)) - 1);
    int x1 = std::min(width - 1, static_cast<int>(std::ceil((right) / TILE_SIZE)) + 1);
    int y0 = std::max(0, static_cast<int>(std::floor(bottom / TILE_SIZE)) - 1);
    int y1 = std::min(height - 1, static_cast<int>(std::ceil((top) / TILE_SIZE)) + 1);

#ifdef DEBUG_VISIBLE_TILES
    std::cout << "tiles: X(" << x0 << "-" << x1 << ") Y(" << y0 << "-" << y1 << ")\n";
#endif

    for (int y = y0; y <= y1; ++y)
    {
        // if (y < 0 || y >= height) continue;

        int rowSize = (int)world[y].size();
        if (rowSize == 0) continue;

        int startX = x0;
        
#ifdef DEBUG_DRAW_CALLINGS
        std::cout << startX << " startX" << std::endl;
#endif
        int endX   = std::min(x1, rowSize);

#ifdef DEBUG_DRAW_CALLINGS
        std::cout << endX << " endX" << std::endl;
#endif

        for (int x = startX; x <= endX; ++x)
        {
            if (x < 0 || x >= rowSize) continue;
            world[y][x].draw(shader);
        }
    }
} 