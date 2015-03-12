#include "levelScene.h"

LevelScene::LevelScene(sf::RenderWindow *window, sf::Event *event, AssetManager *manager)
{
    asset_manager = manager;
    this->window = window;
    this->event = event;
    next_scene = none;

	// Set tile colors
	backgroundTile.setSize(sf::Vector2f(window->getSize().x / (double)WIDTH, window->getSize().y / (double)HEIGHT));

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if ((i+j) % 2 == 0)
				scene[i][j] = 1;
			else
				scene[i][j] = 0;
		}
	}
}

LevelScene::~LevelScene()
{

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
    }
}

void LevelScene::handleLogic()
{

}

void LevelScene::handleRender()
{
    window->clear();

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			switch (scene[i][j]) {
			case 0:
				backgroundTile.setFillColor(sf::Color(242, 241, 239, 255));
				backgroundTile.setPosition(backgroundTile.getSize().x * i, backgroundTile.getSize().y * j);
				window->draw(backgroundTile);
				break;
			case 1:
				backgroundTile.setFillColor(sf::Color(103, 65, 114, 255));
				backgroundTile.setPosition(backgroundTile.getSize().x * i, backgroundTile.getSize().y * j);
				window->draw(backgroundTile);
				break;
			default:
				break;
			}
		}
	}

    window->display();
}
