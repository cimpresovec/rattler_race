#include "snake.h"


Snake::Snake(sf::RenderWindow *window, AssetManager *manager, int scene[HEIGHT][WIDTH], int pickups)
{
	this->window = window;
	this->manager = manager;
	this->tileSize = sf::Vector2f(window->getSize().x / (double)WIDTH, (window->getSize().y - TOP_MARGIN) / (double)HEIGHT);
    this->direction = "up";

    this->scene = scene;
    this->pickups = pickups;

    this->start();
}

Snake::~Snake() { }

int Snake::moveSnake()
{
    int ret = detectCollision();

    for (unsigned int i = 0; i < snake.size(); i++)
    {
        if (i == 0)
        {
            snake[i].rect.setTexture(manager->getTexture("assets/snake.png"));
            snake[i].rect.setTextureRect(sf::Rect<int>(0, 0, 64, 64));
            /*
            if (direction == "down")
                snake[i].rect.setRotation(180);
            else if (direction == "left")
                snake[i].rect.setRotation(-90);
            else if (direction == "right")
                snake[i].rect.setRotation(90);
            */
        }
        else if (i == snake.size() - 1)
        {
            snake[i].rect.setTexture(manager->getTexture("assets/snake.png"));
            snake[i].rect.setTextureRect(sf::Rect<int>(192, 0, 64, 64));
        }
        else
        {
            snake[i].rect.setTexture(manager->getTexture("assets/snake.png"));
            snake[i].rect.setTextureRect(sf::Rect<int>(128, 0, 64, 64));
        }

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

    for (unsigned int i = 1; i < snake.size(); i++)
		snake[i].position = snake[i - 1].lastPosition;

    return ret;
}

void Snake::drawSnake()
{
    for (unsigned int i = 0; i < snake.size(); i++)
    {
		snake[i].rect.setPosition(snake[i].position.x * tileSize.x, snake[i].position.y * tileSize.y + TOP_MARGIN);
		window->draw(snake[i].rect);
	}
}

int Snake::detectCollision()
{
    currentTilePosition = scene[getSnakeTileX(0)][getSnakeTileY(0)];

    if (currentTilePosition == 0) //collision with wall
        return 0;
    else if (snakeSelfCollision(getSnakeTileX(0), getSnakeTileY(0))) //self collision
        return 0;
    else if (currentTilePosition >= 2) //eat item
    {
        this->addPart();
        scene[getSnakeTileX(0)][getSnakeTileY(0)] = 1;
        pickups--;

        if (pickups == 0)
            scene[WIDTH / 2][0] = 1;

        return 1;
    }
    else if (pickups == 0 && getSnakeTileX(0) == 16 && getSnakeTileY(0) == 0)
        return 2;

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
    body.rect.setTextureRect(sf::Rect<int>(128, 0, 64, 64));
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
    head.position.y = HEIGHT - 3;
	head.lastPosition.x = (int)WIDTH / (int)2;
	head.lastPosition.y = HEIGHT - 2;
	head.rect.setTexture(manager->getTexture("assets/snake.png"));
	head.rect.setTextureRect(sf::Rect<int>(0,0,64,64));
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
