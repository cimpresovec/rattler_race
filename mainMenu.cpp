#include "mainMenu.h"
#include <iostream>

using namespace std;

MainMenu::MainMenu(sf::RenderWindow *window, sf::Event *event, AssetManager *manager)
{
    asset_manager = manager;
    this->window = window;
    this->event = event;
    next_scene = none;

	// Menu background
	background.setSize((sf::Vector2f)window->getSize());
	background.setFillColor(sf::Color(242, 241, 239, 255));

	// Lvl1 button and text
	lvl1Btn.setSize(sf::Vector2f(50,50));
	lvl1Btn.setPosition(10, 10);
	lvl1Btn.setFillColor(sf::Color(103, 65, 114, 255));

	lvl1Text.setString("1");
	lvl1Text.setColor(sf::Color(242, 241, 239, 255));
	lvl1Text.setFont(*asset_manager->getFont());
	lvl1Text.setPosition(26,15);

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
}

void MainMenu::handleLogic()
{

}

void MainMenu::handleRender()
{
    window->clear();

	mouseX = sf::Mouse::getPosition(*window).x;
	mouseY = sf::Mouse::getPosition(*window).y;

	cout << mouseX << ", "<< mouseY << endl;

	// Lvl1 button mouse detection
	if (((mouseX > lvl1Btn.getPosition().x) && (mouseX < lvl1Btn.getPosition().x + lvl1Btn.getSize().x)) &&
		((mouseY > lvl1Btn.getPosition().y) && (mouseY < lvl1Btn.getPosition().y + lvl1Btn.getSize().y)))
		lvl1Btn.setFillColor(sf::Color(103, 65, 114, 200));
	else
		lvl1Btn.setFillColor(sf::Color(103, 65, 114, 255));

	// Menu background
	window->draw(background);
	
	// Lvl1 button
	window->draw(lvl1Btn);
	window->draw(lvl1Text);

    window->display();
}
