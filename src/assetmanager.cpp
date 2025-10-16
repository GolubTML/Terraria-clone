#include <filesystem>
#include <fstream>
#include <sstream>

#include "headers/assetmanager.h"
#include "headers/texture.h"

Texture& AssetManager::getTexture(const std::string& name)
{
    // Эта проверка нужна на то, чтобы не загружать повторно текстуру, которая уже есть в памяти.
    auto it = assets.find(name);
    if (it != assets.end())
        return *it->second;

    std::unique_ptr<Texture> tex = std::make_unique<Texture>("textures/" + name, 16, 16);
    Texture& ref = *tex;
    assets[name] = std::move(tex);

    return ref;
}

void AssetManager::loadAll(const std::string& folder)
{   
    std::fstream log("log.txt");
    for (const auto& entry : std::filesystem::recursive_directory_iterator(folder))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".png")
        {   
            std::string path = entry.path().string();
            std::string name = entry.path().lexically_relative(folder).string();

            log <<  path << " name: " << name << std::endl;

            try
            {
                getTexture(name);
            }
            catch (const std::exception& c)
            {
                std::cerr << "Failed load texture " << name << " : " << c.what() << std::endl; 
            }
        }
    }

    log.close();
    std::cout << "Loaded textures: " << assets.size() << std::endl;
}

void AssetManager::clear()
{
    assets.clear();
}