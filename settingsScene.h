#ifndef SETTINGSSCENE_H
#define SETTINGSSCENE_H

#include "gameScene.h"
#include "assetManager.h"

class SettingsScene : public GameScene
{
public:
    SettingsScene(sf::RenderWindow *window, sf::Event *event, AssetManager *manager);
    virtual ~SettingsScene();

    void handleInput();
    void handleLogic();
    void handleRender();
};

#endif // SETTINGSSCENE_H
