#include "levelEditorScene.h"

LevelEditorScene::LevelEditorScene(sf::RenderWindow *window, sf::Event *event, AssetManager *manager)
{
    asset_manager = manager;
    this->window = window;
    this->event = event;
    next_scene = none;
}

LevelEditorScene::~LevelEditorScene()
{

}

void LevelEditorScene::handleInput()
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

void LevelEditorScene::handleLogic()
{

}

void LevelEditorScene::handleRender()
{
    window->clear();

    //CRAP FONT TEST
    sf::Text text("LEVEL editor", *asset_manager->getFont());
    window->draw(text);

    window->display();
}
