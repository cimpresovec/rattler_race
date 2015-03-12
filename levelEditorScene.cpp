#include "levelEditorScene.h"

LevelEditorScene::LevelEditorScene(sf::RenderWindow *window, sf::Event *event, AssetManager *manager)
{
    asset_manager = manager;
    this->window = window;
    this->event = event;
    next_scene = none;

    for (unsigned short i = 0; i < kLEVEL_SIDE_DIMENSION; ++i)
    {
        for (unsigned short j = 0; j < kLEVEL_SIDE_DIMENSION; ++j)
        {
            levelMap[i][j].type = rand() % 2;
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

    static bool setup = false;

    static sf::Text selectedToolText;
    static sf::Text titleText;
    static sf::RectangleShape tile;

    if (!setup)
    {
        titleText.setFont(*asset_manager->getFont());
        titleText.setString("Level editor");
        titleText.setPosition(10, 10);

        selectedToolText.setFont(*asset_manager->getFont());
        selectedToolText.setPosition(10, 40);

        tile.setSize(sf::Vector2f(window->getSize().x / (double)kLEVEL_SIDE_DIMENSION, (window->getSize().y - TOP_MARGIN) / (double)kLEVEL_SIDE_DIMENSION));
        tile.setTexture(asset_manager->getTexture("assets/tiles.png"));

        setup = true;
    }

    std::string str;
    switch (tool)
    {
    case kLevelEditorToolEraser:
        str = "Eraser";
        break;
    case kLevelEditorToolWallPlacer:
        str = "Wall placer";
        break;
    case kLevelEditorToolSpecialPillPlacer:
        str = "Bonus placer";
        break;
    }
    selectedToolText.setString("Tool: " + str);

    window->draw(titleText);
    window->draw(selectedToolText);

    for (int i = 0; i < kLEVEL_SIDE_DIMENSION; i++)
    {
        for (int j = 0; j < kLEVEL_SIDE_DIMENSION; j++)
        {
            switch (levelMap[i][j].type)
            {
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
