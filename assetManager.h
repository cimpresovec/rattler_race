#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class AssetManager
{
private:
    std::map<std::string, sf::Texture*> textures;
    sf::Font *font;
public:
    AssetManager();
    ~AssetManager();

    bool loadTexture(const std::string file);
    sf::Texture* getTexture(const std::string name);
    sf::Font* getFont();
};

#endif // ASSETMANAGER_H
