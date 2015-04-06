#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#define PICKUPS 10

#include "gameScene.h"
#include "assetManager.h"
#include "snake.h"
#include "ball.h"
#include "enemySnake.h"
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>

enum LevelDifficultySetting
{
    kLevelDifficultySettingEasy = 1,
    kLevelDifficultySettingMedium = 2,
    kLevelDifficultySettingHard = 3
};

typedef enum LevelDifficultySetting LevelDifficultySetting;

class LevelScene : public GameScene
{
public:
    LevelScene(sf::RenderWindow *window, sf::Event *event, AssetManager *manager);
    virtual ~LevelScene();

    void handleInput();
    void handleLogic();
    void handleRender();

    void resetLevel();
    void loadLevel(std::string level_name, bool shouldPlacePickups = true);
    void clearLevel();
    void placePickups(int count = 10);
    void placeSpecialPickups(int count = 2);

	void timerHandler();

private:
    int scene[HEIGHT][WIDTH];
	sf::RectangleShape tile;
	Snake *snake;
    int speed;
    unsigned int snakeSpeed;
    unsigned int score;
    LevelDifficultySetting difficultySetting;

    //Level timer
    sf::Clock clock;
    int remainingTime;
	sf::RectangleShape timer;
    double timer_size;
    void initTimer();
    void restartTimer();

    std::vector<Ball> balls;
    std::vector<EnemySnake> enemy_snakes;

    //Sounds related
    sf::Music background_music;

    bool isGameOver;
	bool animation;
    void showGameOverMenu();
	void saveTheHighestCompletedLvl(int lvl);
    void spawnBalls();
    void spawnSnakes();

    void specialEffect();

    bool eventMove;
};

#endif // LEVELSCENE_H
