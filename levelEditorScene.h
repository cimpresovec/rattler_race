#ifndef LEVELEDITORSCENE_H
#define LEVELEDITORSCENE_H

#include "gameScene.h"
#include "assetManager.h"

class LevelEditorScene : public GameScene
{
public:
    LevelEditorScene(sf::RenderWindow *window, sf::Event *event, AssetManager *manager);
    virtual ~LevelEditorScene();

    void handleInput();
    void handleLogic();
    void handleRender();
};

#endif // LEVELEDITORSCENE_H
