#ifndef MAINMENU_H
#define MAINMENU_H

#include "gameScene.h"
#include "assetManager.h"

class MainMenu : public GameScene
{
public:
    MainMenu(AssetManager *manager);
    virtual ~MainMenu();

    void handleInput(sf::RenderWindow *window, sf::Event *event);
    void handleLogic();
    void handleRender(sf::RenderWindow *window);
};

#endif // MAINMENU_H
