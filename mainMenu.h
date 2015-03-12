#ifndef MAINMENU_H
#define MAINMENU_H

#define BUTTONS_IN_ROW 6

#include "gameScene.h"
#include "assetManager.h"

class MainMenu : public GameScene
{
public:
    MainMenu(sf::RenderWindow *window, sf::Event *event, AssetManager *manager);
    virtual ~MainMenu();

    void handleInput();
    void handleLogic();
    void handleRender();
private:
    int mouseX;
    int mouseY;

	double buttonSize = 0;
	double spaceBetween = 0;

	sf::RectangleShape background;

	sf::RectangleShape lvlBtn;
	sf::Text lvlText;

};

#endif // MAINMENU_H
