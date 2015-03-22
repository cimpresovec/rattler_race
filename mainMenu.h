#ifndef MAINMENU_H
#define MAINMENU_H

#define BUTTONS_IN_ROW 6
#define NUMBER_OF_LVLS 30

#include "gameScene.h"
#include "assetManager.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

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

	double buttonSize;
	double spaceBetween;

	double rightBotX;
	double rightBotY;

	int avalibleLvls;

	int numberOfBalls;

	sf::RectangleShape background;

	sf::RectangleShape lvlBtn[NUMBER_OF_LVLS];
	sf::RectangleShape lvlEditorBtn;
	sf::RectangleShape scoreBtn;
	sf::RectangleShape ballsBtn;
	sf::Text ballsText;
	sf::Text lvlText;

};

#endif // MAINMENU_H
