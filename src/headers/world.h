#pragma once
#include <ctime>
#include <cstdlib>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "texture.h"
#include "quad.h"
#include "stb_perlin.h"

class World
{
public:
    int width, height;
    int seed;
    float scale;

    std::vector<std::vector<Quad>> tiles;

    World(int w, int h, int s = static_cast<int>(time(nullptr)), float sc = 0.1f);
    void generate(Texture& stoneTex, Texture& grass);

private:
    float getNoise(float x, float seed, float scale);
};