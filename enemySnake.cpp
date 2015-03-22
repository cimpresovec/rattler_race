#include "enemySnake.h"

EnemySnake::EnemySnake(const int x, const int y, const int win_x, const int win_y, sf::Texture *tex)
{
    this->positions.push_back(sf::Vector2i(x, y));

    render_rect.setSize(sf::Vector2f(win_x/(float)WIDTH, (win_y-TOP_MARGIN)/(float)HEIGHT));
    render_rect.setOrigin(render_rect.getSize().x/2.f, render_rect.getSize().y/2.f);
    render_rect.setTexture(tex);
    render_rect.setTextureRect(sf::IntRect(0, 0, 64, 64));
    render_rect.setFillColor(sf::Color::Red);

    direction = sf::Vector2i(1, 0);

    grow_count = rand() % 5 + 7;

    ate_apple = false;
}

void EnemySnake::handleLogic(int scene[][HEIGHT])
{
    //Do we want to change direction and/or have to change int
    bool change = false;

    //Random factor
    if (rand() % 10 == 0)
    {
        change = true;
    }

    //Collision factor
    sf::Vector2i next_pos = positions[0] + direction;
    if (scene[next_pos.x][next_pos.y] == 0 || scene[next_pos.x][next_pos.y] == -1 || scene[next_pos.x][next_pos.y] == -2)
    {
        change = true;
    }

    //Moving
    if (change)
    {
        //Only 2 directions are available
        sf::Vector2i possible_direction[2];
        bool first_ok = true;
        bool second_ok = true;

        if (direction.x != 0)
        {
            possible_direction[0] = sf::Vector2i(0, 1);
            possible_direction[1] = sf::Vector2i(0, -1);
        }
        else if (direction.y != 0)
        {
            possible_direction[0] = sf::Vector2i(1, 0);
            possible_direction[1] = sf::Vector2i(-1, 0);
        }

        //Check possible direction for walls and crap
        next_pos = positions[0] + possible_direction[0];
        if (scene[next_pos.x][next_pos.y] == 0 || scene[next_pos.x][next_pos.y] == -1 || scene[next_pos.x][next_pos.y] == -2)
        {
            first_ok = false;
        }

        next_pos = positions[0] + possible_direction[1];
        if (scene[next_pos.x][next_pos.y] == 0 || scene[next_pos.x][next_pos.y] == -1 || scene[next_pos.x][next_pos.y] == -2)
        {
            second_ok = false;
        }

        //Set direction to a good oneb
        if (first_ok && second_ok) direction = possible_direction[rand() % 2];
        else if (first_ok) direction = possible_direction[0];
        else if (second_ok) direction = possible_direction[1];
    }

    //Clear tail invisible wall
    scene[positions.back().x][positions.back().y] = 1;

    //Check if we can move in direction
    next_pos = positions[0] + direction;
    if (!(scene[next_pos.x][next_pos.y] == 0 || scene[next_pos.x][next_pos.y] == -1 || scene[next_pos.x][next_pos.y] == -2))
    {
        //We have a direction, move
        if (grow_count > 0)
        {
            positions.push_back(sf::Vector2i(positions.back()));

            for (unsigned int i = positions.size() - 1; i > 0; --i)
            {
                positions[i] = positions[i-1];
            }

            --grow_count;
        }
        else
        {
            for (unsigned int i = positions.size(); i > 0; --i)
            {
                positions[i] = positions[i-1];
            }
        }

        //Check if pickup
        if (scene[next_pos.x][next_pos.y] == 2)
        {
            grow_count++;
            ate_apple = true;
        }

        //Move head
        positions[0] += direction;

        //Set invisible walls
        for (unsigned int i = 0; i < positions.size(); ++i)
        {
            scene[positions[i].x][positions[i].y] = -2;
        }
    }
    //We can't move anywhere, just delete tail
    else
    {
        if (positions.size() > 1)
        {
            positions.erase(positions.begin() + positions.size() - 1);
        }
    }
}

void EnemySnake::handleRender(sf::RenderWindow *window)
{
    //Render each part
    sf::Vector2i diff;
    for (unsigned int i = 0; i < positions.size(); ++i)
    {
        //Head
        if (i == 0)
        {
            render_rect.setTextureRect(sf::IntRect(0, 0, 64, 64));
            if (direction.x > 0) render_rect.setRotation(90);
            else if (direction.x < 0) render_rect.setRotation(-90);
            else if (direction.y > 0) render_rect.setRotation(180);
            else if (direction.y < 0) render_rect.setRotation(0);
        }
        //Tail
        else if (i == positions.size() - 1)
        {
            render_rect.setTextureRect(sf::IntRect(3 * 64, 0, 64, 64));

            //Check position difference
            diff = positions[i] - positions[i-1];
            if (diff.x > 0) render_rect.setRotation(90);
            else if (diff.x < 0) render_rect.setRotation(-90);
            else if (diff.y > 0) render_rect.setRotation(180);
            else if (diff.y < 0) render_rect.setRotation(0);
        }
        //All middle parts
        else
        {
            //Calculate difference
            diff = positions[i+1] - positions[i-1];

            //Horizontal part
            if (diff.y == 0)
            {
                render_rect.setTextureRect(sf::IntRect(2 * 64, 0, 64, 64));
                render_rect.setRotation(90);
            }
            //Vertical
            else if (diff.x == 0)
            {
                render_rect.setTextureRect(sf::IntRect(2 * 64, 0, 64, 64));
                render_rect.setRotation(0);
            }
            //Faking ECK
            else
            {
                render_rect.setTextureRect(sf::IntRect(64, 0, 64, 64));

                //SOME ROTATION SORSERY
                if (positions[i+1].x > positions[i].x)
                {
                    if (positions[i-1].y < positions[i].y) render_rect.setRotation(-90);
                    else render_rect.setRotation(0);
                }
                else if (positions[i+1].x < positions[i].x)
                {
                    if (positions[i-1].y < positions[i].y) render_rect.setRotation(180);
                    else render_rect.setRotation(90);
                }
                else if (positions[i+1].y > positions[i].y)
                {
                    if (positions[i-1].x < positions[i].x) render_rect.setRotation(90);
                    else render_rect.setRotation(0);
                }
                else if (positions[i+1].y < positions[i].y)
                {
                    if (positions[i-1].x < positions[i].x) render_rect.setRotation(180);
                    else render_rect.setRotation(-90);
                }
            }
        }
        render_rect.setPosition(positions[i].x * render_rect.getSize().x + render_rect.getSize().x / 2.f, positions[i].y * render_rect.getSize().y + render_rect.getSize().y / 2.f + TOP_MARGIN);
        window->draw(render_rect);
    }
}
