#include "mainMenu.h"

MainMenu::MainMenu(sf::RenderWindow *window, sf::Event *event, AssetManager *manager)
{
    asset_manager = manager;
    this->window = window;
    this->event = event;
    next_scene = none;

	drziClick = false;

    buttonSize = 0;
	spaceBetween = 0;

	srand(time(NULL));

	// Set avalible lvls
	std::ifstream lvlFile("levels/lvlSave.lvl");
	if (lvlFile.is_open()) {
		std::stringstream ss;
		ss << lvlFile.rdbuf();
		avalibleLvls = atoi(ss.str().c_str()) + 1;
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
	background.setTexture(asset_manager->getTexture("assets/background.png"));

	// LvlEditor button
	lvlEditorBtn.setSize(sf::Vector2f(buttonSize, buttonSize));
	lvlEditorBtn.setTexture(asset_manager->getTexture("assets/menu2.png"));
	lvlEditorBtn.setTextureRect(sf::Rect<int>(0, 256, 256, 256));
	lvlEditorBtn.setPosition(rightBotX, rightBotY);

	// Score button
	scoreBtn.setSize(sf::Vector2f(buttonSize, buttonSize));
	scoreBtn.setTexture(asset_manager->getTexture("assets/menu2.png"));
	scoreBtn.setTextureRect(sf::Rect<int>(0, 0, 256, 256));
	scoreBtn.setPosition(rightBotX - buttonSize - (spaceBetween/2), rightBotY);

	// Ball button
	ballsBtn.setSize(sf::Vector2f(buttonSize, buttonSize));
	ballsBtn.setTexture(asset_manager->getTexture("assets/menu2.png"));
	ballsBtn.setTextureRect(sf::Rect<int>(0, 512, 256, 256));
	ballsBtn.setPosition(rightBotX - buttonSize*2 - (spaceBetween/2)*2, rightBotY);

	// Ball text
	ballsText.setColor(sf::Color(237, 218, 196, 255));
	ballsText.setFont(*asset_manager->getFont());
	ballsText.setPosition(ballsBtn.getPosition().x + buttonSize/2 - 8.5, ballsBtn.getPosition().y + buttonSize / 3 - 0.5);
	ballsText.setString(std::to_string(asset_manager->getNBalls()));

	// Snake button
	snakesBtn.setSize(sf::Vector2f(buttonSize, buttonSize));
	snakesBtn.setTexture(asset_manager->getTexture("assets/menu2.png"));
	snakesBtn.setTextureRect(sf::Rect<int>(0, 1024, 256, 256));
	snakesBtn.setPosition(rightBotX - buttonSize * 3 - (spaceBetween / 3) * 3, rightBotY);

	// Snake text
	snakesText.setColor(sf::Color(237, 218, 196, 255));
	snakesText.setFont(*asset_manager->getFont());
	snakesText.setPosition(snakesBtn.getPosition().x + buttonSize / 2 - 8.5, snakesBtn.getPosition().y + buttonSize / 3 - 0.5);
	snakesText.setString(std::to_string(asset_manager->getNSnakes()));

	// Difficulty text
	difficultyText.setColor(sf::Color(237, 218, 196, 255));
	difficultyText.setFont(*asset_manager->getFont());
	difficultyText.setPosition(snakesBtn.getPosition().x + buttonSize / 2 - 8.5 - buttonSize, snakesBtn.getPosition().y + buttonSize / 3 - 0.5);
	difficultyText.setString("N");

	// Lvl button and text
	for (int i = 0; i < NUMBER_OF_LVLS; i++){
		lvlBtn[i].setSize(sf::Vector2f(buttonSize, buttonSize));
		//lvlBtn[i].setFillColor(sf::Color(29, 29, 26, 180));
		lvlBtn[i].setTexture(asset_manager->getTexture("assets/menu2.png"));
		lvlBtn[i].setTextureRect(sf::Rect<int>(256, 768, 256, 256));
	}

	lvlText.setColor(sf::Color(237, 218, 196, 255));
	lvlText.setFont(*asset_manager->getFont());

	// Title
	title[0].setFont(*asset_manager->getFont());
	title[0].setString("Rattler");
	title[0].setColor(sf::Color(202, 106, 46, 255));
	title[0].setPosition(10, rightBotY);
	title[0].scale(1.5, 1.5);

	title[1].setFont(*asset_manager->getFont());
	title[1].setString("Race");
	title[1].setColor(sf::Color(237, 218, 196, 255));
	title[1].setPosition(20, rightBotY + buttonSize - 38);
	title[1].scale(1.3, 1.3);

	//Background music
    if (background_music.openFromFile("assets/sounds/menu_background.wav"))
    {
    	background_music.setLoop(true);
    	background_music.setVolume(10);
    	background_music.play();
    }
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

			lvlBtn[i].setFillColor(sf::Color(29, 29, 26, 230));
		}
		else
		{
			lvlBtn[i].setFillColor(sf::Color(29, 29, 26, 180));
		}
	}

	// Lvl editor mouse detection
	if (((mouseX > lvlEditorBtn.getPosition().x) && (mouseX < lvlEditorBtn.getPosition().x + buttonSize)) &&
		((mouseY > lvlEditorBtn.getPosition().y) && (mouseY < lvlEditorBtn.getPosition().y + buttonSize))) {

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			next_scene = level_editor;
		}

		lvlEditorBtn.setTextureRect(sf::Rect<int>(256, 256, 256, 256));
	} else {
		lvlEditorBtn.setTextureRect(sf::Rect<int>(0, 256, 256, 256));
	}

	// Highscore mouse detection
	if (((mouseX > scoreBtn.getPosition().x) && (mouseX < scoreBtn.getPosition().x + buttonSize)) &&
		((mouseY > scoreBtn.getPosition().y) && (mouseY < scoreBtn.getPosition().y + buttonSize))) {

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			next_scene = leaderboard;
		}

		scoreBtn.setTextureRect(sf::Rect<int>(256, 0, 256, 256));
	}
	else {
		scoreBtn.setTextureRect(sf::Rect<int>(0, 0, 256, 256));
	}

	// Balls mouse detection
	if (((mouseX > ballsBtn.getPosition().x) && (mouseX < ballsBtn.getPosition().x + buttonSize)) &&
		((mouseY > ballsBtn.getPosition().y) && (mouseY < ballsBtn.getPosition().y + buttonSize))) {

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (!drziClick){
				drziClick = true;
				if (asset_manager->getNBalls() < 3)
					asset_manager->setNBalls(asset_manager->getNBalls() + 1);
				else
					asset_manager->setNBalls(0);
				ballsText.setString(std::to_string(asset_manager->getNBalls()));
			}
		}
		else {
			drziClick = false;
		}

		ballsBtn.setTextureRect(sf::Rect<int>(256, 512, 256, 256));
	}
	else {
		ballsBtn.setTextureRect(sf::Rect<int>(0, 512, 256, 256));
	}

	// Snakes mouse detection
	if (((mouseX > snakesBtn.getPosition().x) && (mouseX < snakesBtn.getPosition().x + buttonSize)) &&
		((mouseY > snakesBtn.getPosition().y) && (mouseY < snakesBtn.getPosition().y + buttonSize))) {

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (!drziClick){
				drziClick = true;
				if (asset_manager->getNSnakes() < 3)
					asset_manager->setNSnakes(asset_manager->getNSnakes() + 1);
				else
					asset_manager->setNSnakes(0);
				snakesText.setString(std::to_string(asset_manager->getNSnakes()));
			}
		}
		else {
			drziClick = false;
		}

		snakesBtn.setTextureRect(sf::Rect<int>(256, 1024, 256, 256));
	}
	else {
		snakesBtn.setTextureRect(sf::Rect<int>(0, 1024, 256, 256));
	}

	// Snakes mouse detection
	if (((mouseX > snakesBtn.getPosition().x - buttonSize) && (mouseX < snakesBtn.getPosition().x)) &&
		((mouseY > snakesBtn.getPosition().y) && (mouseY < snakesBtn.getPosition().y + buttonSize))) {

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (!drziClick){
				std::cout << "Drek" << std::endl;
			}
			drziClick = true;
		}
		else {
			drziClick = false;
		}
	}
}

void MainMenu::handleLogic()
{

}

void MainMenu::handleRender()
{
    window->clear();
    window->setView(window->getDefaultView());

	// Menu background
	window->draw(background);

	// Lvl buttons
	int j = -1;
	for (int i = 0; i < NUMBER_OF_LVLS; i++) {
		if ((i % BUTTONS_IN_ROW) == 0)
			j++;
		lvlBtn[i].setPosition(spaceBetween * ((i%BUTTONS_IN_ROW) + 1) + buttonSize * (i%BUTTONS_IN_ROW), spaceBetween * (j + 1) + buttonSize * j);
		if (i > avalibleLvls-1) {
			lvlText.setString("");
			lvlBtn[i].setTextureRect(sf::Rect<int>(0, 768, 256, 256));
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

	// Score button
	window->draw(scoreBtn);

	// Ball button
	window->draw(ballsBtn);
	window->draw(ballsText);

	// Snakes button
	window->draw(snakesBtn);
	window->draw(snakesText);

	// Difficulty text
	window->draw(difficultyText);

	// Draw tittle
	window->draw(title[0]);
	window->draw(title[1]);

    window->display();
}
