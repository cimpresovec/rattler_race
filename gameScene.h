#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <SFML/Graphics.hpp>

//Game scenes
enum GameSceneType
{
    none = 0,
    quit = 1,
    main_menu = 2
};

//Abstract for game scene
class GameScene
{
public:
    GameSceneType next_scene;

    virtual ~GameScene() {}

    //Required methods
    virtual void handleInput(sf::RenderWindow *window, sf::Event *event) = 0;
    virtual void handleLogic() = 0;
    virtual void handleRender(sf::RenderWindow *window) = 0;
};

#endif // GAMESCENE_H
