#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>

#include "assetManager.h"
#include <vector>
#include <string>

class Snake
{
public:
	Snake(sf::RenderWindow *window);
	~Snake();

	void moveSnake();
	void drawSnake();
	void setDirection(std::string direction);
private:
	std::vector<sf::RectangleShape> snake;
	sf::RenderWindow *window;
	sf::Vector2f tileSize;
	std::string direction;
};

#endif // SNAKE_H

