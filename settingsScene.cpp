#include "settingsScene.h"

SettingsScene::SettingsScene(sf::RenderWindow *window, sf::Event *event, AssetManager *manager)
{
    asset_manager = manager;
    this->window = window;
    this->event = event;
    next_scene = none;
}

SettingsScene::~SettingsScene()
{

}

void SettingsScene::handleInput()
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

void SettingsScene::handleLogic()
{

}

void SettingsScene::handleRender()
{
    window->clear();

    //CRAP FONT TEST
    sf::Text text("Settings", *asset_manager->getFont());
    window->draw(text);

    window->display();
}

