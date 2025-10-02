#pragma once
#include "stb_image.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

class Texture 
{
public:
    GLuint id;
    int width, height;
    int tileWidth, tileHeight;

    Texture(const std::string& path, int tW, int tH);

    void bind();
    void unbind();

    void getUV(int tileX, int tileY, float uv[8]);
};