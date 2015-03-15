#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>

#include "assetManager.h"
#include <vector>
#include <string>
#include <iostream>

class Snake
{
public:
    Snake(sf::RenderWindow *window, int scene[HEIGHT][WIDTH]);
	~Snake();

	void moveSnake();
	void drawSnake();
	void setDirection(std::string direction);
	void detectColision();
	void addPart();
    void newStart();
    bool snakeSelfCollision(int x, int y);

private:
	sf::RenderWindow *window;
	sf::Vector2f tileSize;
	std::string direction;
    int scene[HEIGHT][WIDTH];
    int currentScenePos;

    struct SnakeTile
    {
		SnakeTile() {}
		sf::RectangleShape rect;
		sf::Vector2f position;
		sf::Vector2f lastPosition;
	};

    std::vector<SnakeTile> snake;
};

#endif // SNAKE_H

