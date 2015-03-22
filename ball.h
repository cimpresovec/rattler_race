#ifndef BALL_H
#define BALL_H

#include "assetManager.h"
#include "snake.h"

class Ball
{
private:
    sf::Vector2i position;
    sf::Vector2i speed;
    sf::RectangleShape render_rect;
    int prev_tile;
public:
    Ball(const int x, const int y, const int win_x, const int win_y, sf::Texture *tex);

    void handleLogic(int scene[][HEIGHT]);
    void handleRender(sf::RenderWindow *window);
};

#endif // BALL_H
