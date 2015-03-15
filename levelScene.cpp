#include "levelScene.h"
#include <time.h>

LevelScene::LevelScene(sf::RenderWindow *window, sf::Event *event, AssetManager *manager)
{
    asset_manager = manager;
    this->window = window;
    this->event = event;
    next_scene = none;
	speed = 0;

	// Set tile colors
    tile.setSize(sf::Vector2f(window->getSize().x / (double)WIDTH, (window->getSize().y-TOP_MARGIN) / (double)HEIGHT));
    tile.setTexture(asset_manager->getTexture("assets/tiles1-5.png"));

    //Reset the level
	memset(this->scene, 0, sizeof(this->scene) / sizeof(this->scene[0]));

	//Uncomment the asset_manager stuff to get actual level loading
	const int level_index = 1;//asset_manager->selected_level;
	std::string level = "level_" + std::to_string(level_index) + ".lvl";
	this->loadLevel(level);

    snake = new Snake(window, asset_manager, scene);
}

LevelScene::~LevelScene()
{
	delete snake;
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

        if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Escape)
        {
            next_scene = main_menu;
        }

        if (event->type == sf::Event::KeyPressed && (event->key.code == sf::Keyboard::W || event->key.code == sf::Keyboard::Up))
		{
			if (snake->getDirection() != "up") {
				snake->setDirection("up");
				speed = 0;
				snake->moveSnake();
			}
		}

        if (event->type == sf::Event::KeyPressed && (event->key.code == sf::Keyboard::A || event->key.code == sf::Keyboard::Left))
		{
			if (snake->getDirection() != "left") {
				snake->setDirection("left");
				speed = 0;
				snake->moveSnake();
			}
		}

        if (event->type == sf::Event::KeyPressed && (event->key.code == sf::Keyboard::S || event->key.code == sf::Keyboard::Down))
		{
			if (snake->getDirection() != "down") {
				snake->setDirection("down");
				speed = 0;
				snake->moveSnake();
			}
		}

        if (event->type == sf::Event::KeyPressed && (event->key.code == sf::Keyboard::D || event->key.code == sf::Keyboard::Right))
		{
			if (snake->getDirection() != "right") {
				snake->setDirection("right");
				speed = 0;
				snake->moveSnake();
			}
		}

		if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Q)
		{
			snake->addPart();
		}
    }
}

void LevelScene::handleLogic()
{

}

void LevelScene::handleRender()
{
    window->clear();

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

	// Snake
	speed++;
	snake->drawSnake();
    if (speed == SPEED)
    {
		snake->moveSnake();
		speed = 0;
	}
	// END snake

    window->display();
}

void LevelScene::loadLevel(std::string level_name)
{
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
}
