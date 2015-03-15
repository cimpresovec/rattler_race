#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#define SPEED 8

#include "gameScene.h"
#include "assetManager.h"
#include "snake.h"

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
	Snake *snake;
	int speed = 0;
};

#endif // LEVELSCENE_H
