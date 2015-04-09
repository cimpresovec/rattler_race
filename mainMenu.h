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

	bool drziClick;

	//Sounds related
    sf::Music background_music;

	sf::RectangleShape background;

	sf::RectangleShape lvlBtn[NUMBER_OF_LVLS];
	sf::RectangleShape lvlEditorBtn;
	sf::RectangleShape scoreBtn;
	sf::RectangleShape ballsBtn;
	sf::RectangleShape snakesBtn;

	sf::Text difficultyText;
	sf::Text snakesText;
	sf::Text ballsText;
	sf::Text lvlText;
	sf::Text title[2];

};

#endif // MAINMENU_H
