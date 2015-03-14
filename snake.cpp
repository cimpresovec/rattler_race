#include "snake.h"


Snake::Snake(sf::RenderWindow *window) {
	this->window = window;
	this->tileSize = sf::Vector2f(window->getSize().x / (double)WIDTH, (window->getSize().y - TOP_MARGIN) / (double)HEIGHT);
	direction = "right";

	sf::RectangleShape rect;
	rect.setSize(tileSize);
	snake.push_back(rect);
}


Snake::~Snake() {

}

void Snake::moveSnake() {
	if (direction == "up")
		snake[0].setPosition(snake[0].getPosition().x, snake[0].getPosition().y - tileSize.y);
	else if (direction == "left")
		snake[0].setPosition(snake[0].getPosition().x - tileSize.x, snake[0].getPosition().y);
	else if (direction == "down")
		snake[0].setPosition(snake[0].getPosition().x, snake[0].getPosition().y + tileSize.y);
	else if (direction == "right")
		snake[0].setPosition(snake[0].getPosition().x + tileSize.x, snake[0].getPosition().y);
}

void Snake::drawSnake() {
	for (int i = 0; i < snake.size(); i++)
		window->draw(snake[i]);
}

void Snake::setDirection(std::string direction) {
		this->direction = direction;
}
