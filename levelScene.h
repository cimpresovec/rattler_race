#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#define SPEED 8
#define PICKUPS 10

#include "gameScene.h"
#include "assetManager.h"
#include "snake.h"
#include "ball.h"
#include <string>
#include <fstream>
#include <ctime>

class LevelScene : public GameScene
{
public:
    LevelScene(sf::RenderWindow *window, sf::Event *event, AssetManager *manager);
    virtual ~LevelScene();

    void handleInput();
    void handleLogic();
    void handleRender();

    void resetLevel();
    void loadLevel(std::string level_name);
    void clearLevel();
    void placePickups(int count = 10);

	void timerHandler();

private:
    int scene[HEIGHT][WIDTH];
	sf::RectangleShape tile;
	Snake *snake;
    int speed;
	sf::RectangleShape timer;
	double timer_size;
	time_t start;

    std::vector<Ball> balls;

    bool isGameOver;
    void showGameOverMenu();
};

#endif // LEVELSCENE_H
