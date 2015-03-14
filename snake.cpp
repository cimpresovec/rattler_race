#include "snake.h"


Snake::Snake(sf::RenderWindow *window, int scene[HEIGHT][WIDTH]) {
	this->window = window;
	this->tileSize = sf::Vector2f(window->getSize().x / (double)WIDTH, (window->getSize().y - TOP_MARGIN) / (double)HEIGHT);
	direction = "right";
	
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			this->scene[i][j] = scene[i][j];

	SnakeTile head;
	head.rect.setSize(tileSize);
	head.position.x = 0;
	head.position.y = 0;
	snake.push_back(head);
}


Snake::~Snake() {

}

void Snake::moveSnake() {
	detectColision();

	for (int i = 0; i < snake.size(); i++) {
		snake[i].lastPosition = snake[i].position;
	}

	if (direction == "up")
		snake[0].position.y--;
	else if (direction == "left")
		snake[0].position.x--;
	else if (direction == "down")
		snake[0].position.y++;
	else if (direction == "right")
		snake[0].position.x++;

	for (int i = 1; i < snake.size(); i++) {
		snake[i].position = snake[i - 1].lastPosition;
	}
}

void Snake::drawSnake() {
	for (int i = 0; i < snake.size(); i++){
		snake[i].rect.setPosition(snake[i].position.x * tileSize.x, snake[i].position.y * tileSize.y + TOP_MARGIN);
		window->draw(snake[i].rect);
	}
}

void Snake::detectColision() {
	if (scene[(int)snake[0].position.x][(int)snake[0].position.y] == 0)
		std::cout << "boom" << std::endl;
	else
		std::cout << " " << std::endl;
}

void Snake::addPart() {
	SnakeTile body;
	body.rect.setSize(tileSize);
	body.position.x = snake[snake.size() - 1].lastPosition.x;
	body.position.y = snake[snake.size() - 1].lastPosition.y;
	snake.push_back(body);
}

void Snake::setDirection(std::string direction) {
	if (!((this->direction == "up" && direction == "down") || (this->direction == "down" && direction == "up") || 
		  (this->direction == "left" && direction == "right") || (this->direction == "right" && direction == "left")
		)){
		this->direction = direction;
	}
		
}
