#ifndef ENEMYSNAKE_H
#define ENEMYSNAKE_H

#include <vector>
#include "assetManager.h"


class EnemySnake
{
private:
    std::vector<sf::Vector2i> positions;
    sf::RectangleShape render_rect;

    sf::Vector2i direction;
    unsigned int grow_count;
public:
    EnemySnake(const int x, const int y, const int win_x, const int win_y, sf::Texture *tex);

    void handleLogic(int scene[][HEIGHT]);
    void handleRender(sf::RenderWindow *window);

    bool ate_apple;
};

#endif // ENEMYSNAKE_H
