#include "headers/world.h"

World::World(int w, int h, int s , float sc) : width(w), height(h), seed(s), scale(sc) 
{
}

void World::generate(Texture stoneTex)
{
    tiles.clear();

    for (int y = 0; y < height; ++y)
    {
        std::vector<Quad> row;
        for (int x = 0; x < width; ++x)
        {
            float n = stb_perlin_noise3((x + seed) * scale, (y + seed) * scale, 0.f, 0, 0, 0);

            n = (n + 1.f) / 2.f;


            if (n < 0.5f)
                row.emplace_back(glm::vec2(x * 16.f, y * 16.f), 1.f, 0.f, 16.f, 16.f, &stoneTex, 3.4f, 1.1f);
            else 
                continue;

        }
        tiles.push_back(row);
    }
}