#ifndef MAINMENU_H
#define MAINMENU_H

#include "gameScene.h"
#include "assetManager.h"

class MainMenu : public GameScene
{
public:
    MainMenu(sf::RenderWindow *window, sf::Event *event, AssetManager *manager);
    virtual ~MainMenu();

    void handleInput();
    void handleLogic();
    void handleRender();
};

#endif // MAINMENU_H
