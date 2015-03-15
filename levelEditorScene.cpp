#include "levelEditorScene.h"

LevelEditorScene::LevelEditorScene(sf::RenderWindow *window, sf::Event *event, AssetManager *manager)
{
    asset_manager = manager;
    this->window = window;
    this->event = event;
    next_scene = none;

    this->tool = kLevelEditorToolWallPlacer;
    this->tile_size = sf::Vector2f(window->getSize().x / (double)kLEVEL_SIDE_DIMENSION, (window->getSize().y - TOP_MARGIN) / (double)kLEVEL_SIDE_DIMENSION);

    memset(this->level_tiles, kLevelEditorToolEraser, sizeof(unsigned char) * kLEVEL_SIDE_DIMENSION * kLEVEL_SIDE_DIMENSION);
    for (int i = 0; i < kLEVEL_SIDE_DIMENSION; ++i)
    {
        this->level_tiles[0][i] = kLevelEditorToolWallPlacer;
        this->level_tiles[i][0] = kLevelEditorToolWallPlacer;
        this->level_tiles[kLEVEL_SIDE_DIMENSION - 1][i] = kLevelEditorToolWallPlacer;
        this->level_tiles[i][kLEVEL_SIDE_DIMENSION - 1] = kLevelEditorToolWallPlacer;
    }
}

LevelEditorScene::~LevelEditorScene()
{

}

inline bool exists_test0 (const std::string& name) {
    std::ifstream f(name.c_str());
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }   
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
            case sf::Keyboard::S:
                this->saveLevel("new_level.lvl");
                break;
            default:
                break;
            }
        }
    }

    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        return;

    const int mouseX = sf::Mouse::getPosition(*window).x;
    const int mouseY = sf::Mouse::getPosition(*window).y - 100;

    if (mouseX < 0 || mouseX > 561 || mouseY < 0 || mouseY > 561)
        return;

    //Clicked in the level editing area

    const int rowIndex = (int)floorf(mouseY / tile_size.x);
    const int colIndex = (int)floorf(mouseX / tile_size.y);

    this->level_tiles[colIndex][rowIndex] = (unsigned char)tool;
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

        tile.setSize(this->tile_size);
        tile.setTexture(asset_manager->getTexture("assets/tiles1-5.png"));

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
            switch (level_tiles[i][j])
            {
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

    window->display();
}

void LevelEditorScene::saveLevel(std::string level_name)
{
    std::ofstream file;
    file.open("levels/" + level_name, std::ofstream::out);

    if (!file.is_open())
    {
        std::cout << "Unable to save level: " + level_name + "\r\n";
        return;
    }

    for (int i = 0; i < kLEVEL_SIDE_DIMENSION; ++i)
    {
        for (int j = 0; j < kLEVEL_SIDE_DIMENSION; ++j)
        {
            char c = this->level_tiles[j][i] + '0';
            file.put(c);
        }
        file.put('\n');
    }

    file.close();
}

void LevelEditorScene::loadLevel(std::string level_name)
{
    std::ifstream file;
    file.open("levels/" + level_name, std::ifstream::in);

    if (!file.is_open())
    {
        std::cout << "Level reading error. Unable to load level: " + level_name + "\r\n";
        return;
    }

    char c;
    unsigned short arrayIndex = 0;

    while (file.good())
    {
        c = file.get();
        if (c < '0' || c > '9')
            continue;

        this->level_tiles[arrayIndex % HEIGHT][arrayIndex / WIDTH] = (int)(c - '0');
        ++arrayIndex;
    }

    file.close();
}
