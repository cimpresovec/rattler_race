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

	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			this->scene[i][j] = asset_manager->scene[i][j];

    snake = new Snake(window, scene);
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
