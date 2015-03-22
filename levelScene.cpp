#include "levelScene.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LEVEL_TIME 30000

LevelScene::LevelScene(sf::RenderWindow *window, sf::Event *event, AssetManager *manager)
{
    asset_manager = manager;
    this->window = window;
    this->event = event;
    next_scene = none;
	speed = 0;
	this->score = 0;
	this->difficultySetting = kLevelDifficultySettingMedium;
    this->isGameOver = false;

	// Set tile colors
    tile.setSize(sf::Vector2f(window->getSize().x / (double)WIDTH, (window->getSize().y-TOP_MARGIN) / (double)HEIGHT));
    tile.setTexture(asset_manager->getTexture("assets/tiles1-5.png"));

    //Reset the level
    memset(this->scene, 0, WIDTH * HEIGHT * sizeof(int));

	const int level_index = asset_manager->selected_level;
	std::string level = "level_" + std::to_string(level_index) + ".lvl";
	this->loadLevel(level);

	switch (this->difficultySetting)
	{
	case kLevelDifficultySettingEasy:
		this->snakeSpeed = 12;
		break;
	case kLevelDifficultySettingMedium:
		this->snakeSpeed = 8;
		break;
	case kLevelDifficultySettingHard:
		this->snakeSpeed = 4;
		break;
	}

    snake = new Snake(window, asset_manager, scene);

    //Timer
    initTimer();

    //Balls
    balls.push_back(Ball(2, 2, window->getSize().x, window->getSize().y, asset_manager->getTexture("assets/tiles1-5.png")));

    //Background music
    if (background_music.openFromFile("assets/sounds/background.wav"))
    {
    	background_music.setLoop(true);
    	background_music.setVolume(10);
    	background_music.play();
    }

    eventMove = false;
}

LevelScene::~LevelScene()
{
	delete snake;
}

void LevelScene::initTimer()
{
    timer_size = window->getSize().x - 2 * tile.getSize().x;
    timer.setSize(sf::Vector2f(timer_size, tile.getSize().y));
    timer.setFillColor(sf::Color(68, 183, 64));
    timer.setPosition(sf::Vector2f(tile.getSize().x, TOP_MARGIN - 2 * tile.getSize().y));
    remainingTime = LEVEL_TIME;
    clock.restart();
}

void LevelScene::restartTimer()
{
    timer.setFillColor(sf::Color(68, 183, 64));
    clock.restart();
}

void LevelScene::timerHandler()
{
    remainingTime = LEVEL_TIME - clock.getElapsedTime().asMilliseconds();
    timer.setSize(sf::Vector2f(timer_size * (double)remainingTime / (double)LEVEL_TIME, tile.getSize().y));

    if (remainingTime <= 0)
        isGameOver = true;
    else if (remainingTime <= 5000)
        timer.setFillColor(sf::Color(255, 0, 0));
    else if (remainingTime <= 10000)
        timer.setFillColor(sf::Color(255, 140, 20));
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
                    eventMove = true;
				}
			}

			if (event->type == sf::Event::KeyPressed && (event->key.code == sf::Keyboard::A || event->key.code == sf::Keyboard::Left))
			{
				if (snake->getDirection() != "left") {
					snake->setDirection("left");
                    eventMove = true;
				}
			}

			if (event->type == sf::Event::KeyPressed && (event->key.code == sf::Keyboard::S || event->key.code == sf::Keyboard::Down))
			{
				if (snake->getDirection() != "down") {
					snake->setDirection("down");
                    eventMove = true;
				}
			}

			if (event->type == sf::Event::KeyPressed && (event->key.code == sf::Keyboard::D || event->key.code == sf::Keyboard::Right))
			{
				if (snake->getDirection() != "right") {
					snake->setDirection("right");
                    eventMove = true;
				}
			}
		}
    }
}

void LevelScene::handleLogic()
{
    if (isGameOver)
        return;
    else
        timerHandler();

    //Ball movement
    if (snake->has_moved)
    {
        for (std::vector<Ball>::iterator it = balls.begin(); it != balls.end(); ++it)
        {
            it->handleLogic(scene, *snake);
        }
        snake->has_moved = false;
    }

    if (isGameOver) return;

    //If user pressed a key we move
    if (eventMove)
    {
        eventMove = false;
        snake->moveSnake();
        speed = -1;
    }

    //Normal snake movement
    speed++;
    if (speed == (int)snakeSpeed)
    {
        snake->moveSnake();
		speed = 0;
    }

    const int collisionResult = snake->detectCollision();
    if (collisionResult == 0) //collision
    {
        isGameOver = true;

        static sf::SoundBuffer buffer;
    	static sf::Sound sound;
    	if (!buffer.getSampleCount())
    	{
    		buffer.loadFromFile("assets/sounds/game_over.wav");
    		sound.setBuffer(buffer);
    	}
    	
    	sound.play();
    }
    else if (collisionResult == 1) //ate a pickup
    {
    	static sf::SoundBuffer buffer;
    	static sf::Sound sound;
    	if (!buffer.getSampleCount())
    	{
    		buffer.loadFromFile("assets/sounds/pickup.wav");
    		sound.setBuffer(buffer);
    	}

    	sound.play();

    	this->score += this->difficultySetting;
    }
    if (collisionResult == 2) //level completed
    {
        delete snake;

		// For menu lvl lock
		saveTheHighestCompletedLvl(asset_manager->selected_level);

        asset_manager->selected_level++;

        std::string level = "level_" + std::to_string(asset_manager->selected_level) + ".lvl";
        this->loadLevel(level);
        this->restartTimer();
        snake = new Snake(window, asset_manager, scene);

        static sf::SoundBuffer buffer;
    	static sf::Sound sound;
    	if (!buffer.getSampleCount())
    	{
    		buffer.loadFromFile("assets/sounds/next_level.wav");
    		sound.setBuffer(buffer);
    		sound.setVolume(50);
    	}

    	sound.play();
    }
}

void LevelScene::handleRender()
{
    window->clear();

    //Draw level info
    static sf::Text levelText;
    static sf::Text scoreText;
    static bool setup = false;

    if (!setup)
    {
    	levelText.setFont(*asset_manager->getFont());
    	levelText.setPosition(10, 10);

    	scoreText.setFont(*asset_manager->getFont());
    	scoreText.setPosition(300, 10);
	}

	levelText.setString("Level: " + std::to_string(asset_manager->selected_level));
	scoreText.setString("Score: " + std::to_string(this->score));

    window->draw(levelText);
    window->draw(scoreText);
	window->draw(timer);

	//Render level tiles
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

    //Draw balls
    for (std::vector<Ball>::iterator it = balls.begin(); it != balls.end(); ++it)
    {
        it->handleRender(window);
    }

    //Draw snake
    snake->drawSnake();

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

		window->draw(underlay);
        window->draw(gameOverText);

		int tmp = 1;
		for (int x = 0; x < 2; x++) {
			if (x % 2 == 0)
				tmp = 3;
			else
				tmp = -3;

			for (int i = 0; i < HEIGHT; i++){
				for (int j = 0; j < WIDTH; j++) {
					switch (scene[i][j]) {
					case 0:
						tile.setPosition(tile.getSize().x * i + tmp, tile.getSize().y * j + TOP_MARGIN);
						window->draw(tile);
						break;
					default:
						break;
					}
				}
			}
			window->display();
		}

		return;
	}

    window->display();
}

void LevelScene::resetLevel()
{
	delete snake;

    //Reset level and score
	clearLevel();
	placePickups(PICKUPS);
	this->score = 0;

    //New snake
    snake = new Snake(window, asset_manager, scene);

    restartTimer();
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

void LevelScene::saveTheHighestCompletedLvl(int lvl) {
	std::ifstream lvlFileI("levels/lvlSave.lvl");
	std::stringstream ss;
	ss << lvlFileI.rdbuf();
	std::string lvlString = ss.str();
	lvlFileI.close();

	if (lvlString != ""){
		if (std::stoi(lvlString) < lvl) {
			std::ofstream lvlFileO("levels/lvlSave.lvl");
			if (lvlFileO.is_open()) {
				if (lvl == 30) {
					lvlFileO << 29;
				}
				else
					lvlFileO << lvl;
				lvlFileO.close();
			}
			else
				std::cout << "Unable to open file" << std::endl;
		}
	}
	else {
		std::ofstream lvlFileO("levels/lvlSave.lvl");
		if (lvlFileO.is_open()) {
			lvlFileO << 1;
			lvlFileO.close();
		}
		else
			std::cout << "Unable to open file" << std::endl;
	}
}
