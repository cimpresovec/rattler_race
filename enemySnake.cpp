#include "enemySnake.h"

EnemySnake::EnemySnake(const int x, const int y, const int win_x, const int win_y, sf::Texture *tex)
{
    this->positions.push_back(sf::Vector2i(x, y));

    render_rect.setSize(sf::Vector2f(win_x/(float)WIDTH, (win_y-TOP_MARGIN)/(float)HEIGHT));
    render_rect.setOrigin(render_rect.getSize().x/2.f, render_rect.getSize().y/2.f);
    render_rect.setTexture(tex);
    render_rect.setTextureRect(sf::IntRect(0, 0, 64, 64));
    render_rect.setFillColor(sf::Color::Red);
}

void EnemySnake::handleLogic(int scene[][HEIGHT])
{
    //First check if we are going to hit something
}

void EnemySnake::handleRender(sf::RenderWindow *window)
{
    //Render each part
    for (unsigned int i = 0; i < positions.size(); ++i)
    {
        render_rect.setPosition(positions[i].x * render_rect.getSize().x + render_rect.getSize().x / 2.f, positions[i].y * render_rect.getSize().y + render_rect.getSize().y / 2.f + TOP_MARGIN);
        window->draw(render_rect);
    }
}
