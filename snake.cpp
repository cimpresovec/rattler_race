#include "snake.h"


Snake::Snake(sf::RenderWindow *window, int scene[HEIGHT][WIDTH])
{
	this->window = window;
	this->tileSize = sf::Vector2f(window->getSize().x / (double)WIDTH, (window->getSize().y - TOP_MARGIN) / (double)HEIGHT);
    direction = "up";
	
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
            this->scene[i][j] = scene[i][j];

    this->newStart();
}

Snake::~Snake() { }

void Snake::moveSnake()
{
	detectColision();

    for (int i = 0; i < snake.size(); i++)
    {
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

    for (int i = 1; i < snake.size(); i++)
    {
		snake[i].position = snake[i - 1].lastPosition;
	}
}

void Snake::drawSnake()
{
    for (int i = 0; i < snake.size(); i++)
    {
		snake[i].rect.setPosition(snake[i].position.x * tileSize.x, snake[i].position.y * tileSize.y + TOP_MARGIN);
		window->draw(snake[i].rect);
	}
}

void Snake::detectColision()
{
    currentScenePos = scene[(int)snake[0].position.x][(int)snake[0].position.y];

    if (currentScenePos == 0) //collision with wall
    {
        this->newStart();
    }
    else if (snakeSelfCollision(snake[0].position.x, snake[0].position.y))
    {
        this->newStart();
    }
    else if (currentScenePos == 2 || currentScenePos == 3) //eat item
    {
        this->addPart();
        //scene[(int)snake[0].position.x][(int)snake[0].position.y] = 1;
    }
}

bool Snake::snakeSelfCollision(int x, int y)
{
    for (int i = 1; i < snake.size(); i++)
    {
        if ((int)snake[i].position.x == x && (int)snake[i].position.y == y)
            return true;
    }

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

void Snake::newStart()
{
    snake.clear();

    SnakeTile head;
    head.rect.setSize(tileSize);
    head.position.x = (int)WIDTH / (int)2;
    head.position.y = HEIGHT - 3;
	head.lastPosition.x = (int)WIDTH / (int)2;
	head.lastPosition.y = HEIGHT - 2;
    snake.push_back(head);
    direction = "up";

    this->addPart();
    this->addPart();
}

std::string Snake::getDirection() {
	return direction;
}
