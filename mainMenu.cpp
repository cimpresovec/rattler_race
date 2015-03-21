#include "mainMenu.h"

MainMenu::MainMenu(sf::RenderWindow *window, sf::Event *event, AssetManager *manager)
{
    asset_manager = manager;
    this->window = window;
    this->event = event;
    next_scene = none;

    buttonSize = 0;
	spaceBetween = 0;

	srand(time(NULL));

	// Set avalible lvls
	std::ifstream lvlFile("levels/lvlSave.lvl");
	if (lvlFile.is_open()) {
		std::stringstream ss;
		ss << lvlFile.rdbuf();
		avalibleLvls = std::stoi(ss.str()) + 1;
	}
	else
		avalibleLvls = 1;


	// Dvet gumbov pa 1/10 gumba razmaka
	buttonSize = (double)(window->getSize().x / (BUTTONS_IN_ROW + 2));
	spaceBetween = (double)(buttonSize*2 / (BUTTONS_IN_ROW+1));

	// Menu desno spodaj
	rightBotX = window->getSize().x - buttonSize - spaceBetween;
	rightBotY = window->getSize().y - buttonSize - spaceBetween;


	// Menu background
	background.setSize((sf::Vector2f)window->getSize());
	background.setFillColor(sf::Color(242, 241, 239, 255));

	// LvlEditor button
	lvlEditorBtn.setSize(sf::Vector2f(buttonSize, buttonSize));
	lvlEditorBtn.setFillColor(sf::Color(103, 65, 114, 255));
	lvlEditorBtn.setPosition(rightBotX, rightBotY);

	// Lvl button and text
	for (int i = 0; i < NUMBER_OF_LVLS; i++){
		lvlBtn[i].setSize(sf::Vector2f(buttonSize, buttonSize));
		lvlBtn[i].setFillColor(sf::Color(103, 65, 114, 255));
	}

	lvlText.setColor(sf::Color(242, 241, 239, 255));
	lvlText.setFont(*asset_manager->getFont());
}

MainMenu::~MainMenu()
{

}

void MainMenu::handleInput()
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
            next_scene = quit;
        }
        if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::L)
        {
            next_scene = level;
        }
        if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::E)
        {
            next_scene = level_editor;
        }
        if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::S)
        {
            next_scene = setting;
        }
    }

	// Mouse input
	mouseX = sf::Mouse::getPosition(*window).x;
	mouseY = sf::Mouse::getPosition(*window).y;

	// Lvl button mouse detection
	// Load levels here
	
	int j = -1;
	for (int i = 0; i < avalibleLvls; ++i) 
	{
		if ((i % BUTTONS_IN_ROW) == 0)
			j++;

		if (((mouseX > lvlBtn[i].getPosition().x) && (mouseX < lvlBtn[i].getPosition().x + buttonSize)) &&
			((mouseY > lvlBtn[i].getPosition().y) && (mouseY < lvlBtn[i].getPosition().y + buttonSize)))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				asset_manager->selected_level = i + 1;
				next_scene = level;
			}

			lvlBtn[i].setFillColor(sf::Color(103, 65, 114, 200));
		}
		else
		{
			lvlBtn[i].setFillColor(sf::Color(103, 65, 114, 255));
		}
	}

	// Lvl editor mouse detection
	if (((mouseX > lvlEditorBtn.getPosition().x) && (mouseX < lvlEditorBtn.getPosition().x + buttonSize)) &&
		((mouseY > lvlEditorBtn.getPosition().y) && (mouseY < lvlEditorBtn.getPosition().y + buttonSize))) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			next_scene = level_editor;
		}

		lvlEditorBtn.setFillColor(sf::Color(103, 65, 114, 200));
	} else {
		lvlEditorBtn.setFillColor(sf::Color(103, 65, 114, 255));
	}
}

void MainMenu::handleLogic()
{

}

void MainMenu::handleRender()
{
    window->clear();

	// Menu background
	window->draw(background);

	// Lvl buttons
	int j = -1;
	for (int i = 0; i < NUMBER_OF_LVLS; i++) {
		if ((i % BUTTONS_IN_ROW) == 0)
			j++;
		lvlBtn[i].setPosition(spaceBetween * ((i%BUTTONS_IN_ROW) + 1) + buttonSize * (i%BUTTONS_IN_ROW), spaceBetween * (j + 1) + buttonSize * j);
		if (i > avalibleLvls-1) {
			lvlText.setString(" ??");
		}
		else if (i < 9)
			lvlText.setString("0" + std::to_string(i + 1));
		else
			lvlText.setString(std::to_string(i + 1));
		lvlText.setPosition(((spaceBetween + buttonSize / 2.0) + (buttonSize + spaceBetween) * (i%BUTTONS_IN_ROW)) - (buttonSize / 4.0), (spaceBetween + buttonSize / 2.0) + (buttonSize + spaceBetween) * (j%BUTTONS_IN_ROW) - (buttonSize / 4.0));
		window->draw(lvlBtn[i]);
	    window->draw(lvlText);
	}

	// LvlEditor button
	window->draw(lvlEditorBtn);

    window->display();
}
