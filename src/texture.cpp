#include "headers/texture.h"

Texture::Texture(const std::string& path, int tW, int tH) : tileWidth(tW), tileHeight(tH) 
{
    int channels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 4);
    if (!data) 
    {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return;
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(data);
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::getUV(int tileX, int tileY, float uv[8])
{
    float u = (tileX * tileWidth) / (float)width;
    float v = (tileY * tileHeight) / (float)height;
    float u2 = ((tileX+1) * tileWidth) / (float)width;
    float v2 = ((tileY+1) * tileHeight) / (float)height;

    uv[0] = u;
    uv[1] = v;

    uv[2] = u2;
    uv[3] = v;

    uv[4] = u;
    uv[5] = v2;

    uv[6] = u2;
    uv[7] = v2;
}