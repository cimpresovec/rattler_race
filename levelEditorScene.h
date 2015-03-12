#ifndef LEVELEDITORSCENE_H
#define LEVELEDITORSCENE_H

#include "gameScene.h"
#include "assetManager.h"

#ifndef kLEVEL_SIDE_DIMENSION
    #define kLEVEL_SIDE_DIMENSION 33
#endif

enum LevelEditorTool
{
    kLevelEditorToolEraser = 0,
    kLevelEditorToolWallPlacer = 1,
    kLevelEditorToolSpecialPillPlacer = 2
};

typedef enum LevelEditorTool LevelEditorTool;

struct LevelTile
{
    sf::RectangleShape renderRect;
    char type;

};

typedef struct LevelTile LevelTile;

class LevelEditorScene : public GameScene
{
private:
    LevelTile levelMap[kLEVEL_SIDE_DIMENSION][kLEVEL_SIDE_DIMENSION];
    LevelEditorTool tool;

public:
    LevelEditorScene(sf::RenderWindow *window, sf::Event *event, AssetManager *manager);
    virtual ~LevelEditorScene();

    void handleInput();
    void handleLogic();
    void handleRender();
};

#endif // LEVELEDITORSCENE_H
