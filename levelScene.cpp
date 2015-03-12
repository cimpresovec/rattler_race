#include "levelScene.h"
#include <time.h>

#define TOP_MARGIN 100

LevelScene::LevelScene(sf::RenderWindow *window, sf::Event *event, AssetManager *manager)
{
    asset_manager = manager;
    this->window = window;
    this->event = event;
    next_scene = none;

    srand(time(NULL));

	// Set tile colors
    tile.setSize(sf::Vector2f(window->getSize().x / (double)WIDTH, (window->getSize().y-TOP_MARGIN) / (double)HEIGHT));
    tile.setTexture(asset_manager->getTexture("assets/tiles.png"));

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || j == 0 || i == 32 || j == 32)
				scene[i][j] = 1;
			else
            {
                scene[i][j] = rand() % 2;
                if (scene[i][j] == 1)
                    scene[i][j] = rand() % 2;
            }
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

    for (int i = 0; i < HEIGHT; i++){
		for (int j = 0; j < WIDTH; j++) {
			switch (scene[i][j]) {
			case 0:
                tile.setTextureRect(sf::Rect<int>(0,0,64,64));
                tile.setPosition(tile.getSize().x * i, tile.getSize().y * j + TOP_MARGIN);
				window->draw(tile);
				break;
            case 1:
                tile.setTextureRect(sf::Rect<int>(64,0,64,64));
                tile.setPosition(tile.getSize().x * i, tile.getSize().y * j + TOP_MARGIN);
				window->draw(tile);
				break;
			default:
				break;
			}
		}
	}

    window->display();
}
