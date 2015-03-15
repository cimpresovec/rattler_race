#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#define SPEED 8

#include "gameScene.h"
#include "assetManager.h"
#include "snake.h"
#include <string>
#include <fstream>

class LevelScene : public GameScene
{
public:
    LevelScene(sf::RenderWindow *window, sf::Event *event, AssetManager *manager);
    virtual ~LevelScene();

    void handleInput();
    void handleLogic();
    void handleRender();

    void loadLevel(std::string level_name);
    void clearLevel();
    void placePickups(int count = 10);

private:
    int scene[HEIGHT][WIDTH];
	sf::RectangleShape tile;
	Snake *snake;
	int speed;
    bool levelDone;
};

#endif // LEVELSCENE_H
