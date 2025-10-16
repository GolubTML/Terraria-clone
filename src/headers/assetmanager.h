#pragma once
#include <unordered_map>
#include <string>
#include <memory>

#include "texture.h"

class Texture;

class AssetManager
{
private:
    static inline std::unordered_map<std::string, std::unique_ptr<Texture>> assets;

public:
    static Texture& getTexture(const std::string& name);

    static void loadAll(const std::string& folder);
    static void clear();
};