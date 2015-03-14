#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#define WIDTH 33
#define HEIGHT 33

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
private:
	int scene[HEIGHT][WIDTH];
	sf::RectangleShape tile;
};

#endif // LEVELSCENE_H
