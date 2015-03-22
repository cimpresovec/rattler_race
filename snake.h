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

    void moveSnake();
	void drawSnake();
	void setDirection(std::string direction);
	std::string getDirection();
    int detectCollision();
	void addPart();
    void start();
    bool snakeSelfCollision(int x, int y);
    int getSnakeTileX(int index);
    int getSnakeTileY(int index);
	void remoaveHead();

    bool has_moved;

    struct SnakeTile
    {
        SnakeTile() {}
        sf::RectangleShape rect;
        sf::Vector2f position;
        sf::Vector2f lastPosition;
    };

    std::vector<SnakeTile> snake;
private:
    inline void setSelfWall();
    inline void clearSelfWall();

	sf::RenderWindow *window;
	AssetManager *manager;
	sf::Vector2f tileSize;
	std::string direction;
    int (*scene)[HEIGHT];
    int currentTilePosition;
    int pickups;
};

#endif // SNAKE_H

