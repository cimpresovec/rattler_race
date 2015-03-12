#include "levelEditorScene.h"

LevelEditorScene::LevelEditorScene(sf::RenderWindow *window, sf::Event *event, AssetManager *manager)
{
    asset_manager = manager;
    this->window = window;
    this->event = event;
    next_scene = none;

    const int winWidth = window->getSize().x;
    const int winHeight = window->getSize().x;

    for (unsigned short i = 0; i < kLEVEL_SIDE_DIMENSION; ++i)
    {
        for (unsigned short j = 0; j < kLEVEL_SIDE_DIMENSION; ++j)
        {
//            levelMap[i][j].renderRect.setOrigin();
        }
    }
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
            next_scene = quit;

        if (event->type == sf::Event::KeyReleased)
        {
            switch (event->key.code)
            {
            case sf::Keyboard::Escape:
                next_scene = main_menu;
                break;
            case sf::Keyboard::C:
                tool = kLevelEditorToolEraser;
                break;
            case sf::Keyboard::V:
                tool = kLevelEditorToolWallPlacer;
                break;
            case sf::Keyboard::B:
                tool = kLevelEditorToolSpecialPillPlacer;
                break;
            default:
                break;
            }
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

    for (unsigned short i = 0; i < kLEVEL_SIDE_DIMENSION; ++i)
    {
        for (unsigned short j = 0; j < kLEVEL_SIDE_DIMENSION; ++j)
        {

        }
    }

    window->display();
}
