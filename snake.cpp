#include "snake.h"


Snake::Snake(sf::RenderWindow *window, AssetManager *manager, int scene[HEIGHT][WIDTH])
{
	this->window = window;
	this->manager = manager;
	this->tileSize = sf::Vector2f(window->getSize().x / (double)WIDTH, (window->getSize().y - TOP_MARGIN) / (double)HEIGHT);
    this->direction = "up";

    this->scene = scene;

    this->pickups = 0;
    for (int i = 1; i < HEIGHT - 1; i++)
        for (int j = 1; j < WIDTH - 1; j++)
            if (scene[i][j] >= 2)
                this->pickups++;

    has_moved = false;

    this->start();
}

Snake::~Snake() { }

inline void Snake::setSelfWall()
{
    for (unsigned int i = 0; i < snake.size(); ++i)
    {
        scene[(int)snake[i].position.x][(int)snake[i].position.y] = -1;
    }
}

inline void Snake::clearSelfWall()
{
    for (unsigned int i = 0; i < snake.size(); ++i)
    {
        scene[(int)snake[i].position.x][(int)snake[i].position.y] = 1;
    }
}

void Snake::moveSnake()
{
    //For balls and CPU snakes
    has_moved = true;

    for (unsigned int i = 0; i < snake.size(); i++)
    {
        if (i == 0)
            snake[i].rect.setTextureRect(sf::Rect<int>(0, 0, 64, 64));
        else if (i == snake.size() - 1)
            snake[i].rect.setTextureRect(sf::Rect<int>(192, 0, 64, 64));
        else
            snake[i].rect.setTextureRect(sf::Rect<int>(128, 0, 64, 64));

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

    //Move to new positions
    for (unsigned int i = 1; i < snake.size(); i++)
    {
        snake[i].position = snake[i - 1].lastPosition;
    }
}

void Snake::drawSnake()
{
    for (unsigned int i = 0; i < snake.size(); i++)
    {
        snake[i].rect.setPosition(snake[i].position.x * tileSize.x + tileSize.x/2, snake[i].position.y * tileSize.y + TOP_MARGIN + tileSize.y/2);

        if (i == 0)
        {
            if (direction == "up")
                snake[i].rect.setRotation(0.0);
            else if (direction == "left")
                snake[i].rect.setRotation(-90.0);
            else if (direction == "right")
                snake[i].rect.setRotation(90.0);
            else if (direction == "down")
                snake[i].rect.setRotation(180.0);
        }
        else if (i == snake.size() - 1) //tail
        {
            if (snake[i-1].position.x > snake[i].position.x)
                snake[i].rect.setRotation(-90.0);
            else if (snake[i-1].position.x < snake[i].position.x)
                snake[i].rect.setRotation(90.0);
            else if (snake[i-1].position.y > snake[i].position.y)
                snake[i].rect.setRotation(0.0);
            else if (snake[i-1].position.y < snake[i].position.y)
                snake[i].rect.setRotation(180.0);
        }
        else //tiles between head and tail
        {
            snake[i].rect.setTextureRect(sf::Rect<int>(128, 0, 64, 64));

            if (snake[i-1].position.x == snake[i+1].position.x) //vertical texture
                snake[i].rect.setRotation(0.0);
            else if (snake[i-1].position.y == snake[i+1].position.y) //horizontal texture
                snake[i].rect.setRotation(90.0);
            else //turn texture
            {
                snake[i].rect.setTextureRect(sf::Rect<int>(64, 0, 64, 64));

                if (snake[i-1].position.x < snake[i+1].position.x && snake[i-1].position.y > snake[i+1].position.y)
                {
                    if (snake[i-1].position.x == snake[i].position.x)
                        snake[i].rect.setRotation(0.0);
                    else
                        snake[i].rect.setRotation(180.0);
                }
                else if (snake[i-1].position.x > snake[i+1].position.x && snake[i-1].position.y < snake[i+1].position.y)
                {
                    if (snake[i-1].position.x == snake[i].position.x)
                        snake[i].rect.setRotation(180.0);
                    else
                        snake[i].rect.setRotation(0.0);
                }
                else if (snake[i-1].position.x < snake[i+1].position.x && snake[i-1].position.y < snake[i+1].position.y)
                {
                    if (snake[i-1].position.x == snake[i].position.x)
                        snake[i].rect.setRotation(-90.0);
                    else
                        snake[i].rect.setRotation(90.0);
                }
                else if (snake[i-1].position.x > snake[i+1].position.x && snake[i-1].position.y > snake[i+1].position.y)
                {
                    if (snake[i-1].position.x == snake[i].position.x)
                        snake[i].rect.setRotation(90.0);
                    else
                        snake[i].rect.setRotation(-90.0);
                }
            }
        }

		window->draw(snake[i].rect);
	}
}

int Snake::detectCollision()
{
    //Clear collision tiles from underneeth, so we can normaly check for collision
    //clearSelfWall();

    currentTilePosition = scene[getSnakeTileX(0)][getSnakeTileY(0)];

    if (currentTilePosition == 0 || currentTilePosition == -1) //collision with wall
        return 0;
    else if (snakeSelfCollision(getSnakeTileX(0), getSnakeTileY(0))) //self collision
        return 0;
    else if (currentTilePosition >= 2) //eat item
    {
        this->addPart();
        scene[getSnakeTileX(0)][getSnakeTileY(0)] = 1;
        pickups--;

        if (pickups == 0)
            scene[(WIDTH - 1) / 2][0] = 1;

        return 1;
    }
    else if (pickups == 0 && getSnakeTileX(0) == (int)WIDTH / 2 && getSnakeTileY(0) == 0) //level completed
        return 2;

    //Set collision tiles for balls and other snakes
    //setSelfWall();

    return -1;
}

bool Snake::snakeSelfCollision(int x, int y)
{
    for (unsigned int i = 1; i < snake.size(); i++)
        if (getSnakeTileX(i) == x && getSnakeTileY(i) == y)
            return true;

    return false;
}

void Snake::addPart()
{
    SnakeTile body;
    body.rect.setSize(tileSize);
	body.position.x = snake[snake.size() - 1].lastPosition.x;
    body.position.y = snake[snake.size() - 1].lastPosition.y;
	body.lastPosition.x = snake[snake.size() - 1].lastPosition.x;
	body.lastPosition.y = snake[snake.size() - 1].lastPosition.y;
    body.rect.setTexture(manager->getTexture("assets/snake.png"));
    body.rect.setTextureRect(sf::Rect<int>(194, 0, 64, 64));
    body.rect.setOrigin(tileSize.x / 2.0, tileSize.y / 2.0);
	snake.push_back(body);
}

void Snake::setDirection(std::string direction)
{
	if (!((this->direction == "up" && direction == "down") || (this->direction == "down" && direction == "up") || 
		  (this->direction == "left" && direction == "right") || (this->direction == "right" && direction == "left")
        ))
    {
		this->direction = direction;
	}
}

void Snake::start()
{
    SnakeTile head;
    head.rect.setSize(tileSize);
    head.position.x = (int)WIDTH / (int)2;
    head.position.y = HEIGHT - 2;
	head.lastPosition.x = (int)WIDTH / (int)2;
	head.lastPosition.y = HEIGHT-1;
	head.rect.setTexture(manager->getTexture("assets/snake.png"));
	head.rect.setTextureRect(sf::Rect<int>(0,0,64,64));
    head.rect.setOrigin(tileSize.x / 2.0, tileSize.y / 2.0);
    snake.push_back(head);
    direction = "up";

    this->addPart();
	this->addPart();
}

std::string Snake::getDirection()
{
	return direction;
}

int Snake::getSnakeTileX(int index)
{
    return (int)snake[index].position.x;
}

int Snake::getSnakeTileY(int index)
{
    return (int)snake[index].position.y;
}

void Snake::remoaveHead() {
	snake.erase(snake.begin());
}
