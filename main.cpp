#include <SFML/Graphics.hpp>
#include "mainMenu.h"
#include "assetManager.h"

int main()
{
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(800, 600), "Rattler Race");
    sf::Event *event = new sf::Event();

    //Asset manager
    //Image, fonts, sounds should only be loaded once, and then used where needed
    AssetManager *asset_manager = new AssetManager();
    asset_manager->loadTexture("assets/image.png");

    window->setFramerateLimit(60);

    GameScene *current_scene = new MainMenu(asset_manager);
    bool game_loop = true;

    while (game_loop)
    {
        //Event handling
        current_scene->handleInput(window, event);

        //Logic
        current_scene->handleLogic();

        //Render
        current_scene->handleRender(window);

        //Scene switching
        if (current_scene->next_scene != none)
        {
            switch (current_scene->next_scene)
            {
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
