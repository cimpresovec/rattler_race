#include "levelScene.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int kLevelPlayTime = 30;

LevelScene::LevelScene(sf::RenderWindow *window, sf::Event *event, AssetManager *manager)
{
    asset_manager = manager;
    this->window = window;
    this->event = event;
    next_scene = none;
	speed = 0;

    this->isGameOver = false;

	// Set tile colors
    tile.setSize(sf::Vector2f(window->getSize().x / (double)WIDTH, (window->getSize().y-TOP_MARGIN) / (double)HEIGHT));
    tile.setTexture(asset_manager->getTexture("assets/tiles1-5.png"));

    //Reset the level
	memset(this->scene, 0, WIDTH * HEIGHT * sizeof(int));

	const int level_index = asset_manager->selected_level;
	std::string level = "level_" + std::to_string(level_index) + ".lvl";
	this->loadLevel(level);

    snake = new Snake(window, asset_manager, scene);

	// Timer
	timer_size = window->getSize().x - 2 * tile.getSize().x;
	timer.setSize(sf::Vector2f(timer_size, tile.getSize().y));
	timer.setFillColor(sf::Color(68, 183, 64, 255));
	timer.setPosition(sf::Vector2f(tile.getSize().x, TOP_MARGIN - 2 * tile.getSize().y));
	start = clock();
}

LevelScene::~LevelScene()
{
	delete snake;
}
void LevelScene::timerHandler()
{
	time_t time_to_solve;

	time_to_solve = kLevelPlayTime - (int)((clock() - start) / CLOCKS_PER_SEC);
	//zmanjsaj velikost
	timer.setSize(sf::Vector2f(timer_size * (double)time_to_solve / (double)kLevelPlayTime, tile.getSize().y));

	if (time_to_solve <= 0)
        isGameOver = true;
}

void LevelScene::handleInput()
{
    while (window->pollEvent(*event))
    {
        //This should be handled everywhere
        if (event->type == sf::Event::Closed)
        {
            next_scene = quit;
        }

        if (event->type == sf::Event::KeyReleased)
        {
        	if (event->key.code == sf::Keyboard::Escape)
        	{
            	next_scene = main_menu;
            }
            else if (event->key.code == sf::Keyboard::R && isGameOver)
            {
                isGameOver = false;
            	resetLevel();
            }
        }

		if (!isGameOver){
			if (event->type == sf::Event::KeyPressed && (event->key.code == sf::Keyboard::W || event->key.code == sf::Keyboard::Up))
			{
				if (snake->getDirection() != "up") {
					snake->setDirection("up");
					speed = 0;

					if (snake->moveSnake() == 0)
						isGameOver = true;
				}
			}

			if (event->type == sf::Event::KeyPressed && (event->key.code == sf::Keyboard::A || event->key.code == sf::Keyboard::Left))
			{
				if (snake->getDirection() != "left") {
					snake->setDirection("left");
					speed = 0;
					if (snake->moveSnake() == 0)
						isGameOver = true;
				}
			}

			if (event->type == sf::Event::KeyPressed && (event->key.code == sf::Keyboard::S || event->key.code == sf::Keyboard::Down))
			{
				if (snake->getDirection() != "down") {
					snake->setDirection("down");
					speed = 0;
					if (snake->moveSnake() == 0)
						isGameOver = true;
				}
			}

			if (event->type == sf::Event::KeyPressed && (event->key.code == sf::Keyboard::D || event->key.code == sf::Keyboard::Right))
			{
				if (snake->getDirection() != "right") {
					snake->setDirection("right");
					speed = 0;
					if (snake->moveSnake() == 0)
						isGameOver = true;
				}
			}
		}
    }
}

void LevelScene::handleLogic()
{
	timerHandler();

    if (snake->detectCollision() == 0) //collision
    {
        isGameOver = true;
    }
    if (snake->detectCollision() == 2) //level completed
    {
        // GO TO NEXT LEVEL
        delete snake;
        start = clock();
        timer_size = window->getSize().x - 2 * tile.getSize().x;

        asset_manager->selected_level++;
        std::string level = "level_" + std::to_string(asset_manager->selected_level) + ".lvl";
        this->loadLevel(level);
        snake = new Snake(window, asset_manager, scene);
    }
}

void LevelScene::handleRender()
{
    window->clear();

	window->draw(timer);

    for (int i = 0; i < HEIGHT; i++){
		for (int j = 0; j < WIDTH; j++) {
			switch (scene[i][j]) {
			case 0:
				tile.setTextureRect(sf::Rect<int>(0, 0, 64, 64));
				tile.setPosition(tile.getSize().x * i, tile.getSize().y * j + TOP_MARGIN);
				window->draw(tile);
				break;
            case 1:
				tile.setTextureRect(sf::Rect<int>(64, 0, 64, 64));
				tile.setPosition(tile.getSize().x * i, tile.getSize().y * j + TOP_MARGIN);
				window->draw(tile);
				break;
			case 2:
				tile.setTextureRect(sf::Rect<int>(128, 0, 64, 64));
				tile.setPosition(tile.getSize().x * i, tile.getSize().y * j + TOP_MARGIN);
				window->draw(tile);
				break;
			case 3:
				tile.setTextureRect(sf::Rect<int>(192, 0, 64, 64));
				tile.setPosition(tile.getSize().x * i, tile.getSize().y * j + TOP_MARGIN);
				window->draw(tile);
				break;
			default:
				break;
			}
		}
    }

    if (isGameOver)
	{
		static bool gameOverSetup = false;	
		static sf::RectangleShape underlay;
		static sf::Text gameOverText;

		if (!gameOverSetup)
		{
			gameOverText.setFont(*asset_manager->getFont());
        	gameOverText.setString("GAME OVER\n  R to restart");
        	gameOverText.setPosition(190, 240);

        	underlay.setPosition(135, 200);
        	underlay.setSize(sf::Vector2f(300, 150));
        	underlay.setFillColor(sf::Color(0, 0, 0, 255));
			gameOverSetup = true;
		}

        snake->drawSnake();
		window->draw(underlay);
        window->draw(gameOverText);
		window->display();

		return;
	}

	// Snake
	speed++;
	snake->drawSnake();

    if (speed == SPEED && !isGameOver)
    {
        snake->moveSnake();
		speed = 0;
    }

    window->display();
}

void LevelScene::resetLevel()
{
	timer.setSize(sf::Vector2f(timer_size, tile.getSize().y));
	delete snake;
    snake = new Snake(window, asset_manager, scene);
	clearLevel();
	placePickups(PICKUPS);
	start = clock();
}

void LevelScene::loadLevel(std::string level_name)
{
	memset(this->scene, 0, WIDTH * HEIGHT * sizeof(int));
	
	std::ifstream file;
	file.open("levels/" + level_name, std::ifstream::in);

	if (!file.is_open())
	{
		std::cout << "Level reading error. Unable to load level: " + level_name + "\r\n";
		return;
	}

	char c;
	unsigned short arrayIndex = 0;

	while (file.good())
	{
		c = file.get();
		if (c < '0' || c > '9')
			continue;

		this->scene[arrayIndex % HEIGHT][arrayIndex / WIDTH] = (int)(c - '0');
		++arrayIndex;
	}

	file.close();

    placePickups(PICKUPS);
}

void LevelScene::clearLevel()
{
	for (int i = 0; i < WIDTH; ++i)
		for (int j = 0; j < HEIGHT; ++j)
			if (this->scene[i][j] == 2)
				this->scene[i][j] = 1;

    this->scene[(WIDTH-1)/2][0] = 0;
}

void LevelScene::placePickups(int count)
{
	int loopCounter = 0;
	while (count > 0 && loopCounter < 1000000)
	{
		const int x = rand() % WIDTH;
		const int y = rand() % WIDTH;
		if (this->scene[y][x] == 1)
		{
			this->scene[y][x] = 2;
			count--;
		}

		++loopCounter;
	}
}
