#include "mainMenu.h"

MainMenu::MainMenu(sf::RenderWindow *window, sf::Event *event, AssetManager *manager)
{
    asset_manager = manager;
    this->window = window;
    this->event = event;
    next_scene = none;

	srand(time(NULL));

	// Dvet gumbov pa 1/10 gumba razmaka
	buttonSize = (double)(window->getSize().x / (BUTTONS_IN_ROW + 2));
	spaceBetween = (double)(buttonSize*2 / (BUTTONS_IN_ROW+1));

	// Menu background
	background.setSize((sf::Vector2f)window->getSize());
	background.setFillColor(sf::Color(242, 241, 239, 255));

	// Lvl button and text
	for (int i = 0; i < 30; i++){
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
	for (int i = 0; i < 30; i++) {
		if ((i % BUTTONS_IN_ROW) == 0)
			j++;

		if (((mouseX > lvlBtn[i].getPosition().x) && (mouseX < lvlBtn[i].getPosition().x + buttonSize)) &&
			((mouseY > lvlBtn[i].getPosition().y) && (mouseY < lvlBtn[i].getPosition().y + buttonSize))) {

			lvlBtn[i].setFillColor(sf::Color(103, 65, 114, 200));

			switch (i) {
			case 0:
				// Level 1
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					for (int i = 0; i < HEIGHT; i++) {
						for (int j = 0; j < WIDTH; j++) {
							if (i == 0 || j == 0 || i == (33 - 1) || j == (33 - 1))
								asset_manager->scene[i][j] = 0;
							else if (i == 10 && j > 5 && j < 27) {
								asset_manager->scene[i][j] = 0;
							}
							else if (i == 22 && j > 5 && j < 27) {
								asset_manager->scene[i][j] = 0;
							}
							else {
								int tmp = rand() % 100;
								if (tmp > 98) {
									asset_manager->scene[i][j] = 2;
								}
								else if (tmp > 97) {
									asset_manager->scene[i][j] = 3;
								}
								else {
									asset_manager->scene[i][j] = 1;
								}
							}
						}
					}
					next_scene = level;
				}
				break;
			case 1:
				// Level 2
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					for (int i = 0; i < HEIGHT; i++) {
						for (int j = 0; j < WIDTH; j++) {
							if (i == 0 || j == 0 || i == (33 - 1) || j == (33 - 1))
								asset_manager->scene[i][j] = 0;
							else if (j == 10 && i > 5 && i < 27) {
								asset_manager->scene[i][j] = 0;
							}
							else if (j == 22 && i > 5 && i < 27) {
								asset_manager->scene[i][j] = 0;
							}
							else {
								int tmp = rand() % 100;
								if (tmp > 98) {
									asset_manager->scene[i][j] = 2;
								}
								else if (tmp > 97) {
									asset_manager->scene[i][j] = 3;
								}
								else {
									asset_manager->scene[i][j] = 1;
								}
							}
						}
					}
					next_scene = level;
				}
				break;
			case 2:
				// Level 3
				break;
			case 3:
				// Level 4
				break;
			case 4:
				// Level 5
				break;
			default:
				break;
			}

		}
		else
			lvlBtn[i].setFillColor(sf::Color(103, 65, 114, 255));
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
	for (int i = 0; i < 30; i++) {
		if ((i % BUTTONS_IN_ROW) == 0)
			j++;
		lvlBtn[i].setPosition(spaceBetween * ((i%BUTTONS_IN_ROW) + 1) + buttonSize * (i%BUTTONS_IN_ROW), spaceBetween * (j + 1) + buttonSize * j);
		if (i < 9)
			lvlText.setString("0"+std::to_string(i+1));
		else
			lvlText.setString(std::to_string(i + 1));
		lvlText.setPosition(((spaceBetween + buttonSize / 2.0) + (buttonSize + spaceBetween) * (i%BUTTONS_IN_ROW)) - (buttonSize / 4.0), (spaceBetween + buttonSize / 2.0) + (buttonSize + spaceBetween) * (j%BUTTONS_IN_ROW) - (buttonSize / 4.0));
		window->draw(lvlBtn[i]);
		window->draw(lvlText);
	}

    window->display();
}
