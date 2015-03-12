#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include "gameScene.h"
#include "assetManager.h"

class LevelScene : public GameScene
{
public:
    LevelScene(sf::RenderWindow *window, sf::Event *event, AssetManager *manager);
    virtual ~LevelScene();

    void handleInput();
    void handleLogic();
    void handleRender();
};

#endif // LEVELSCENE_H
