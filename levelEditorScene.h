#ifndef LEVELEDITORSCENE_H
#define LEVELEDITORSCENE_H

#include "gameScene.h"
#include "assetManager.h"

#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

#ifndef kLEVEL_SIDE_DIMENSION
    #define kLEVEL_SIDE_DIMENSION 33
#endif

#ifndef TOP_MARGIN
    #define TOP_MARGIN 100
#endif


enum LevelEditorTool
{
    kLevelEditorToolEraser = 1,
    kLevelEditorToolWallPlacer = 0,
    kLevelEditorToolPickupPlacer = 2,
    kLevelEditorToolSpecialPillPlacer = 3
};

typedef enum LevelEditorTool LevelEditorTool;

class LevelEditorScene : public GameScene
{
private:
    sf::Vector2f tile_size;
    unsigned char level_tiles[kLEVEL_SIDE_DIMENSION][kLEVEL_SIDE_DIMENSION];
    LevelEditorTool tool;
    bool shouldClear;

    //Sounds related
    sf::Music background_music;

public:
    LevelEditorScene(sf::RenderWindow *window, sf::Event *event, AssetManager *manager);
    virtual ~LevelEditorScene();

    void handleInput();
    void handleLogic();
    void handleRender();


    void saveLevel(std::string level_name);
    void loadLevel(std::string level_name);
};

#endif // LEVELEDITORSCENE_H

