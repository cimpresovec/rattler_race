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
    Snake(sf::RenderWindow *window, AssetManager *manager, int scene[HEIGHT][WIDTH]);
	~Snake();

    int moveSnake();
	void drawSnake();
	void setDirection(std::string direction);
	std::string getDirection();
    int detectCollision();
	void addPart();
    void start();
    bool snakeSelfCollision(int x, int y);
    int getSnakeTileX(int index);
    int getSnakeTileY(int index);

private:
	sf::RenderWindow *window;
	AssetManager *manager;
	sf::Vector2f tileSize;
	std::string direction;
    int (*scene)[HEIGHT];
    int currentTilePosition;
    int pickableItemsNum;

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

