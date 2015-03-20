#include "ball.h"

Ball::Ball(const int x, const int y, const int win_x, const int win_y, sf::Texture *tex)
{
    this->position.x = x;
    this->position.y = y;

    this->speed = sf::Vector2i(1, 1);

    render_rect.setSize(sf::Vector2f(win_x/(float)WIDTH, (win_y-TOP_MARGIN)/(float)HEIGHT));
    render_rect.setOrigin(render_rect.getSize().x/2.f, render_rect.getSize().y/2.f);
    render_rect.setTexture(tex);
    render_rect.setTextureRect(sf::IntRect(3*64, 0, 64, 64));

    this->prev_tile = 1;
}

void Ball::handleLogic(int scene[][HEIGHT], const Snake &snake)
{
    //Restore scene tile
    scene[position.x][position.y] = prev_tile;

    //First do horizontal movement
    position.x += speed.x;

    //Check next collision
    if (scene[position.x][position.y] == 0)
    {
        position.x -= speed.x;
        speed.x = -speed.x;
    }
    else
    {
        for (unsigned int i = 1; i < snake.snake.size(); ++i)
        {
            if (position.x == snake.snake[i].position.x && position.y == snake.snake[i].position.y)
            {
                position.x -= speed.x;
                speed.x = -speed.x;
            }
        }
    }

    position.y += speed.y;

    //Check collision
    if (scene[position.x][position.y] == 0)
    {
        position.y -= speed.y;
        speed.y = -speed.y;
    }
    else
    {
        for (unsigned int i = 1; i < snake.snake.size(); ++i)
        {
            if (position.x == snake.snake[i].position.x && position.y == snake.snake[i].position.y)
            {
                position.y -= speed.y;
                speed.y = -speed.y;
            }
        }
    }

    //Set hazard on scene
    prev_tile = scene[position.x][position.y];
    scene[position.x][position.y] = 0;
}

void Ball::handleRender(sf::RenderWindow *window)
{
    //Set to position and draw
    render_rect.setPosition(position.x*render_rect.getSize().x+render_rect.getSize().x/2.f, position.y*render_rect.getSize().y+TOP_MARGIN+render_rect.getSize().y/2.f);
    window->draw(render_rect);
}
