#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#define SPEED 8
#define PICKUPS 10

#include "gameScene.h"
#include "assetManager.h"
#include "snake.h"
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

    void loadLevel(std::string level_name);
    void clearLevel();
    void placePickups(int count = 10);

	void timerHandler();
	void timerReset();

private:
    int scene[HEIGHT][WIDTH];
	sf::RectangleShape tile;
	Snake *snake;
    int speed;
	sf::RectangleShape timer;
	double timer_size;
	time_t start;

};

#endif // LEVELSCENE_H
