#include <iostream>

#include "assetManager.h"

AssetManager::AssetManager()
{
    font = new sf::Font();
    if (!font->loadFromFile("assets/Ubuntu-L.ttf"))
        std::cerr << "Can't load font: Ubuntu-L.ttf\n";
}

AssetManager::~AssetManager()
{
    for (std::map<std::string, sf::Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
        delete it->second;

    textures.clear();

    delete font;
}

bool AssetManager::loadTexture(const std::string file)
{
    sf::Texture *tex = new sf::Texture();
    if (!tex->loadFromFile(file))
    {
        std::cerr << "Can't load file: " << file << '\n';
        return false;
    }
    tex->setSmooth(false);
    textures[file] = tex;
    return true;
}

sf::Texture* AssetManager::getTexture(const std::string name)
{
    if (textures.find(name) != textures.end())
        return textures[name];
    
    return NULL;
}

sf::Font* AssetManager::getFont()
{
    return font;
}
