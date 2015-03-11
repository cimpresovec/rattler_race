#include <iostream>

#include "assetManager.h"

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
    for (std::map<std::string, sf::Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
    {
        delete it->second;
    }
    textures.clear();
}

bool AssetManager::loadTexture(const std::string file)
{
    sf::Texture *tex = new sf::Texture();
    if (!tex->loadFromFile(file))
    {
        std::cerr << "Can't load file: " << file << '\n';
        return false;
    }
    textures[file] = tex;
    return true;
}

sf::Texture* AssetManager::getTexture(const std::string name)
{
    if (textures.find(name) != textures.end())
    {
        return textures[name];
    }
    return NULL;
}
