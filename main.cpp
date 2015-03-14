#include <SFML/Graphics.hpp>
#include "mainMenu.h"
#include "levelScene.h"
#include "levelEditorScene.h"
#include "settingsScene.h"
#include "assetManager.h"

int main()
{
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(561, 661), "Rattler Race");
    sf::Event *event = new sf::Event();

    //Asset manager
    //Image, fonts, sounds should only be loaded once, and then used where needed
    AssetManager *asset_manager = new AssetManager();
    asset_manager->loadTexture("assets/tiles1-5.png");

    window->setFramerateLimit(60);

    GameScene *current_scene = new MainMenu(window, event, asset_manager);
    bool game_loop = true;

    while (game_loop)
    {
        //Event handling
        current_scene->handleInput();

        //Logic
        current_scene->handleLogic();

        //Render
        current_scene->handleRender();

        //Scene switching
        if (current_scene->next_scene != none)
        {
            switch (current_scene->next_scene)
            {
            case level:
            {
				int scene[HEIGHT][WIDTH];
				for (int i = 0; i < HEIGHT; i++) {
					for (int j = 0; j < WIDTH; j++) {
						if (i == 0 || j == 0 || i == (33 - 1) || j == (33 - 1))
							scene[i][j] = 1;
						else if ( i == 10 && j > 5 && j < 27) {
							scene[i][j] = 1;
						}
						else if (i == 22 && j > 5 && j < 27) {
							scene[i][j] = 1;
						}
						else {
							scene[i][j] = 0;
						}
					}
				}
                GameScene *new_scene = new LevelScene(window, event, asset_manager, scene);
                delete current_scene;
                current_scene = new_scene;
                break;
            }
            case main_menu:
            {
                GameScene *new_scene = new MainMenu(window, event, asset_manager);
                delete current_scene;
                current_scene = new_scene;
                break;
            }
            case level_editor:
            {
                GameScene *new_scene = new LevelEditorScene(window, event, asset_manager);
                delete current_scene;
                current_scene = new_scene;
                break;
            }
            case setting:
            {
                GameScene *new_scene = new SettingsScene(window, event, asset_manager);
                delete current_scene;
                current_scene = new_scene;
                break;
            }
            case quit:
            {
                game_loop = false;
                delete current_scene;
                break;
            }
            default:
                break;
            }
        }
    }

    //Clean up
    delete window;
    delete event;
    delete asset_manager;

    return 0;
}
