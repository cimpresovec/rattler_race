#include "mainMenu.h"

MainMenu::MainMenu(AssetManager *manager)
{
    asset_manager = manager;
    next_scene = none;
}

MainMenu::~MainMenu()
{

}

void MainMenu::handleInput(sf::RenderWindow *window, sf::Event *event)
{
    while (window->pollEvent(*event))
    {
        //This should be handled everywhere
        if (event->type == sf::Event::Closed)
        {
            next_scene = quit;
        }
    }
}

void MainMenu::handleLogic()
{

}

void MainMenu::handleRender(sf::RenderWindow *window)
{
    window->clear();

    sf::RectangleShape durka(sf::Vector2f(300, 200));
    durka.setTexture(asset_manager->getTexture("assets/image.png"));
    durka.setPosition(100, 100);
    window->draw(durka);

    window->display();
}
