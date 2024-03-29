#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "assetManager.h"

//Game scenes
enum GameSceneType
{
    none = 0,
    quit = 1,
    main_menu = 2,
    level = 3,
    level_editor = 4,
    setting = 5,
    leaderboard = 6
};

//Abstract for game scene
class GameScene
{
public:
    GameSceneType next_scene;
    AssetManager *asset_manager;
    sf::RenderWindow *window;
    sf::Event *event;

    virtual ~GameScene() {}

    //Required methods
    virtual void handleInput() = 0;
    virtual void handleLogic() = 0;
    virtual void handleRender() = 0;
};

#endif // GAMESCENE_H
