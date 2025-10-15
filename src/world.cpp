#include "headers/world.h"

World::World(int w, int h, int s , float sc) : width(w), height(h), seed(s), scale(sc) 
{
}

void World::generate(Texture& stoneTex, Texture& dirtTex, Texture& grass)
{
    tiles.clear();

    for (int y = 0; y < height; ++y)
    {
        std::vector<Quad> row;
        for (int x = 0; x < width; ++x)
        {
            float n = getNoise(x, seed, scale);
            n = (n + 1.f) / 2.f;

            int groundHeight = (int)(n * height * 0.5f + height * 0.25f);

            if (y > groundHeight) 
            {
                row.emplace_back(true, true);
                continue;
            }

            if (y == groundHeight)
                row.emplace_back(glm::vec2(x * 16.f, y * 16.f), 1.f, 0.f, 16.f, 16.f, &grass, 1.1f, 2.3f);

            if (y < groundHeight)
            {
                if (y < groundHeight - 30.f)
                {
                    float caveNoise = stb_perlin_noise3(x * scale, y * scale, seed * 0.1f, 0.f, 0.f, 0.f);

                    const float caveThreshold = -0.1f;
                    
                    if (caveNoise < caveThreshold)
                    {
                        row.emplace_back(true, true);
                        continue;
                    }
                    else
                    {
                        row.emplace_back(glm::vec2(x * 16.f, y * 16.f), 1.f, 0.f, 16.f, 16.f, &stoneTex, 1.f, 1.f);
                        continue;
                    }
                }

                row.emplace_back(glm::vec2(x * 16.f, y * 16.f), 1.f, 0.f, 16.f, 16.f, &dirtTex, 3.4f, 1.1f);
            }
        }
        tiles.push_back(row);
    }
}

float World::getNoise(float x, float seed, float scale)
{
    // Базовый шум верхенего словя мира. Построен на основе fractional Brownian motion(фрактального шума).
    // Содержит такие переменные как total, amp, freq и maxValue.
    // total - отвечает за количество волн в шуме.
    // amp - амлитуда, то есть сила шума.
    // freq - множитель частоты.
    // maxValue - максимальное значение, для того чтобы сделать нормализацию до -1, 1.
    float total = 0; 
    float amp = 1.f;
    float freq = 1.f;
    float maxValue = 0;

    for (int i = 0; i < 4; ++i)
    {
        // По факту, чем меньше freq, тем менее четче будет шум.
        total += stb_perlin_noise3(x * scale * freq, seed * 0.1f, 0.f, 0, 0, 0) * amp; 
        maxValue += amp; // - Нужно для нормализовки в будущем.
        amp *= 0.5f; // - Для того, чтобы следующие октавы были меньше. Эффект холмов.
        freq *= 2.f; // - Для того, чтобы следующие октавы былы менее детолезированы.
    }
    
    // Нормализуем и возращаем наш шум.
    return total / maxValue;
}