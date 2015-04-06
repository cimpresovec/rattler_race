#include "levelScene.h"
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#define LEVEL_TIME 30000

LevelScene::LevelScene(sf::RenderWindow *window, sf::Event *event, AssetManager *manager)
{
    asset_manager = manager;
    this->window = window;
    this->event = event;
    next_scene = none;
	speed = 0;
	this->score = 0;
	this->difficultySetting = kLevelDifficultySettingMedium;
	this->animation = true;
    this->isGameOver = false;

	// Set tile colors
	const int level_index = asset_manager->selected_level;
    tile.setSize(sf::Vector2f(window->getSize().x / (double)WIDTH, (window->getSize().y-TOP_MARGIN) / (double)HEIGHT));
	if (level_index < 6)
	{
		tile.setTexture(asset_manager->getTexture("assets/tiles1-5.png"));
	}
	else if (level_index > 5 && level_index < 11)
	{
		tile.setTexture(asset_manager->getTexture("assets/tiles6-10.png"));
	}
	else if (level_index > 10 && level_index < 16)
	{
		tile.setTexture(asset_manager->getTexture("assets/tiles11-15.png"));
	}
	else //if (level_index > 15 && level_index < 21)
	{
		tile.setTexture(asset_manager->getTexture("assets/tiles16-20.png"));
	}
    

    //Reset the level
    memset(this->scene, 0, WIDTH * HEIGHT * sizeof(int));

	
	std::string level = "level_" + std::to_string(level_index) + ".lvl";
	this->loadLevel(level);

	switch (this->difficultySetting)
	{
	case kLevelDifficultySettingEasy:
		this->snakeSpeed = 12;
		break;
	case kLevelDifficultySettingMedium:
		this->snakeSpeed = 8;
		break;
	case kLevelDifficultySettingHard:
		this->snakeSpeed = 4;
		break;
	}

    snake = new Snake(window, asset_manager, scene);

    //Timer
    initTimer();

    //Balls
    spawnBalls();

    //Snakes
    spawnSnakes();

    //Background music
    if (background_music.openFromFile("assets/sounds/background.wav"))
    {
    	background_music.setLoop(true);
    	background_music.setVolume(10);
    	background_music.play();
    }

    eventMove = false;

    srand(time(NULL));
}

LevelScene::~LevelScene()
{
	delete snake;
}

void LevelScene::initTimer()
{
    timer_size = window->getSize().x - 2 * tile.getSize().x;
    timer.setSize(sf::Vector2f(timer_size, tile.getSize().y));
    timer.setFillColor(sf::Color(68, 183, 64));
    timer.setPosition(sf::Vector2f(tile.getSize().x, TOP_MARGIN - 2 * tile.getSize().y));
    remainingTime = LEVEL_TIME;
    clock.restart();
}

void LevelScene::restartTimer()
{
    timer.setFillColor(sf::Color(68, 183, 64));
    clock.restart();
}

void LevelScene::timerHandler()
{
    remainingTime = LEVEL_TIME - clock.getElapsedTime().asMilliseconds();
    timer.setSize(sf::Vector2f(timer_size * (double)remainingTime / (double)LEVEL_TIME, tile.getSize().y));

    if (remainingTime <= 0)
        isGameOver = true;
    else if (remainingTime <= 5000)
        timer.setFillColor(sf::Color(255, 0, 0));
    else if (remainingTime <= 10000)
        timer.setFillColor(sf::Color(255, 140, 20));
}

void LevelScene::handleInput()
{
    while (window->pollEvent(*event))
    {
        //This should be handled everywhere
        if (event->type == sf::Event::Closed)
        {
            next_scene = quit;
        }

        if (event->type == sf::Event::KeyReleased)
        {
        	if (event->key.code == sf::Keyboard::Escape)
        	{
            	next_scene = main_menu;
            }
            else if (event->key.code == sf::Keyboard::R && isGameOver)
            {
                isGameOver = false;
				animation = true;
            	resetLevel();
            }
        }

		if (!isGameOver){
			if (event->type == sf::Event::KeyPressed && (event->key.code == sf::Keyboard::W || event->key.code == sf::Keyboard::Up))
			{
				if (snake->getDirection() != "up") {
					snake->setDirection("up");
                    eventMove = true;
				}
			}

			if (event->type == sf::Event::KeyPressed && (event->key.code == sf::Keyboard::A || event->key.code == sf::Keyboard::Left))
			{
				if (snake->getDirection() != "left") {
					snake->setDirection("left");
                    eventMove = true;
				}
			}

			if (event->type == sf::Event::KeyPressed && (event->key.code == sf::Keyboard::S || event->key.code == sf::Keyboard::Down))
			{
				if (snake->getDirection() != "down") {
					snake->setDirection("down");
                    eventMove = true;
				}
			}

			if (event->type == sf::Event::KeyPressed && (event->key.code == sf::Keyboard::D || event->key.code == sf::Keyboard::Right))
			{
				if (snake->getDirection() != "right") {
					snake->setDirection("right");
                    eventMove = true;
				}
			}
		}
    }
}

//Clear balls and spawn new ones
void LevelScene::spawnBalls()
{
    balls.clear();

    //TODO set this to settings
    int n_balls = 0;

    while (n_balls > 0)
    {
        //Random location untill we are on floor tile
        while (true)
        {
            int rand_x = rand() % WIDTH;
            int rand_y = rand() % HEIGHT;

            if (scene[rand_x][rand_y] == 1)
            {
                balls.push_back(Ball(rand_x, rand_y, window->getSize().x, window->getSize().y, asset_manager->getTexture("assets/ball.png")));
                break;
            }
        }

        --n_balls;
    }
}

//Clear snakes and create new ones
void LevelScene::spawnSnakes()
{
    enemy_snakes.clear();

    //TODO set this to settings
    int n_snakes = 0;

    while (n_snakes > 0)
    {
        //Random location untill we are on floor tile
        while (true)
        {
            int rand_x = rand() % WIDTH;
            int rand_y = rand() % HEIGHT;

            if (scene[rand_x][rand_y] == 1)
            {
                enemy_snakes.push_back(EnemySnake(rand_x, rand_y, window->getSize().x, window->getSize().y, asset_manager->getTexture("assets/snake.png")));
                break;
            }
        }

        --n_snakes;
    }
}

void LevelScene::handleLogic()
{
    if (isGameOver)
        return;
    else
        timerHandler();

    //Ball and enemy snake movement
    if (snake->has_moved)
    {
        for (std::vector<Ball>::iterator it = balls.begin(); it != balls.end(); ++it)
        {
            it->handleLogic(scene);
        }
        for (std::vector<EnemySnake>::iterator it = enemy_snakes.begin(); it != enemy_snakes.end(); ++it)
        {
            it->handleLogic(scene);
            if (it->ate_apple)
            {
                it->ate_apple = false;
                snake->eatPickup();
            }
        }
        snake->has_moved = false;
    }

    if (isGameOver) return;

    //If user pressed a key we move
    if (eventMove)
    {
        eventMove = false;
        snake->moveSnake();
        speed = -1;
    }

    //Normal snake movement
    speed++;
    if (speed == (int)snakeSpeed)
    {
        snake->moveSnake();
		speed = 0;
    }

    const int collisionResult = snake->detectCollision();
    if (collisionResult == 0) //collision
    {
        isGameOver = true;

        static sf::SoundBuffer buffer;
    	static sf::Sound sound;
    	if (!buffer.getSampleCount())
    	{
    		buffer.loadFromFile("assets/sounds/game_over.wav");
    		sound.setBuffer(buffer);
    	}
    	
    	sound.play();
    }
    else if (collisionResult == 1) //ate a pickup
    {
    	static sf::SoundBuffer buffer;
    	static sf::Sound sound;
    	if (!buffer.getSampleCount())
    	{
    		buffer.loadFromFile("assets/sounds/pickup.wav");
    		sound.setBuffer(buffer);
    	}

    	sound.play();

    	this->score += this->difficultySetting;
    }
    else if (collisionResult == 3) //Ate a special item - apply a random effect
    {
        this->specialEffect();
    }
    else if (collisionResult == 2) //level completed
    {
        delete snake;

		// For menu lvl lock
		saveTheHighestCompletedLvl(asset_manager->selected_level);

        asset_manager->selected_level++;

        std::string level = "level_" + std::to_string(asset_manager->selected_level) + ".lvl";
        this->loadLevel(level);
        this->restartTimer();
        snake = new Snake(window, asset_manager, scene);
        spawnBalls();
        spawnSnakes();

        static sf::SoundBuffer buffer;
    	static sf::Sound sound;
    	if (!buffer.getSampleCount())
    	{
    		buffer.loadFromFile("assets/sounds/next_level.wav");
    		sound.setBuffer(buffer);
    		sound.setVolume(50);
    	}

    	sound.play();
    }
}

void LevelScene::handleRender()
{
    window->clear();

    //Draw level info
    static sf::Text levelText;
    static sf::Text scoreText;
    static bool setup = false;

    if (!setup)
    {
    	levelText.setFont(*asset_manager->getFont());
    	levelText.setPosition(10, 10);

    	scoreText.setFont(*asset_manager->getFont());
    	scoreText.setPosition(300, 10);
	}

	levelText.setString("Level: " + std::to_string(asset_manager->selected_level));
	scoreText.setString("Score: " + std::to_string(this->score));

    window->draw(levelText);
    window->draw(scoreText);
	window->draw(timer);

	//Render level tiles
    for (int i = 0; i < HEIGHT; i++){
		for (int j = 0; j < WIDTH; j++) {
			switch (scene[i][j]) {
			case 0:
				tile.setTextureRect(sf::Rect<int>(0, 0, 64, 64));
				tile.setPosition(tile.getSize().x * i, tile.getSize().y * j + TOP_MARGIN);
				window->draw(tile);
				break;
            case 1:
				tile.setTextureRect(sf::Rect<int>(64, 0, 64, 64));
				tile.setPosition(tile.getSize().x * i, tile.getSize().y * j + TOP_MARGIN);
				window->draw(tile);
				break;
			case 2:
				tile.setTextureRect(sf::Rect<int>(128, 0, 64, 64));
				tile.setPosition(tile.getSize().x * i, tile.getSize().y * j + TOP_MARGIN);
				window->draw(tile);
				break;
			case 3:
				tile.setTextureRect(sf::Rect<int>(192, 0, 64, 64));
				tile.setPosition(tile.getSize().x * i, tile.getSize().y * j + TOP_MARGIN);
				window->draw(tile);
				break;
            case -1:
                tile.setTextureRect(sf::Rect<int>(64, 0, 64, 64));
                tile.setPosition(tile.getSize().x * i, tile.getSize().y * j + TOP_MARGIN);
                window->draw(tile);
                break;
            case -2:
                tile.setTextureRect(sf::Rect<int>(64, 0, 64, 64));
                tile.setPosition(tile.getSize().x * i, tile.getSize().y * j + TOP_MARGIN);
                window->draw(tile);
                break;
			default:
				break;
			}
		}
    }

    //Draw balls and enemy snakes
    for (std::vector<Ball>::iterator it = balls.begin(); it != balls.end(); ++it)
    {
        it->handleRender(window);
    }
    for (std::vector<EnemySnake>::iterator it = enemy_snakes.begin(); it != enemy_snakes.end(); ++it)
    {
        it->handleRender(window);
    }

    if (isGameOver)
	{
		if (animation) {
			animation = false;
			int tmp = 1;
			int zastavica = false;
			for (int x = 0; x < 4; x++) {
				switch (x % 2) {
					case 0:
						if (zastavica){
							tmp = -15;
							zastavica = false;
						}
						else {
							tmp = 15;
							zastavica = true;
						}
						break;
					default:
						tmp = 0;
						break;
				}

				for (int i = 0; i < HEIGHT; i++){
					for (int j = 0; j < WIDTH; j++) {
						switch (scene[i][j]) {
						case 0:
							tile.setPosition(tile.getSize().x * i + tmp, tile.getSize().y * j + tmp + TOP_MARGIN);
							window->draw(tile);
							break;
						default:
							break;
						}
					}
				}
				window->display();
			}
		}
		else {
			static bool gameOverSetup = false;
			static sf::RectangleShape underlay;
			static sf::Text gameOverText;

			if (!gameOverSetup)
			{
				gameOverText.setFont(*asset_manager->getFont());
				gameOverText.setString("GAME OVER\n  R to restart");
				gameOverText.setPosition(190, 240);

				underlay.setPosition(135, 200);
				underlay.setSize(sf::Vector2f(300, 150));
				underlay.setFillColor(sf::Color(0, 0, 0, 180));
				gameOverSetup = true;
			}

			snake->drawSnake();
			window->draw(underlay);
			window->draw(gameOverText);	
			window->display();
		}

		return;
	}
	else {
		//Draw snake
		snake->drawSnake();
	}

    window->display();
}

void LevelScene::resetLevel()
{
    //Let's check the score
    std::fstream file;
    file.open("data/leaderboard.snek", std::fstream::in | std::fstream::out);

    if (file.is_open())
    {
        std::string buff;
        std::string tmp;
        std::string content = "";
        int tmpScore;
        bool writtenScore = false;

        for (int i = 0; i < 5; ++i)
        {
            std::getline(file, buff, '\n');
            tmp = buff.substr(buff.find_first_of(";") + 1);
            tmpScore = std::atoi(tmp.c_str());

            if (tmpScore >= this->score || writtenScore)
            {
                tmp = buff;
            }
            else
            {
                tmp = "player;" + std::to_string(this->score);
                writtenScore = true;
            }

            content += tmp + "\n";
        }
        
        file.seekg(0);
        file.write(content.c_str(), content.length());
        file.close();
    }
    else
    {
        printf("Error saving your high score.\r\n");
    }

	delete snake;

    //Reset level and score
	const int level_index = asset_manager->selected_level;
	std::string level = "level_" + std::to_string(level_index) + ".lvl";
	this->loadLevel(level);
	this->score = 0;

    //Reset balls
    spawnBalls();
    spawnSnakes();

    //New snake
    snake = new Snake(window, asset_manager, scene);

    restartTimer();
}

void LevelScene::loadLevel(std::string level_name, bool shouldPlacePickups)
{
	memset(this->scene, 0, WIDTH * HEIGHT * sizeof(int));
	
	std::ifstream file;
	file.open("levels/" + level_name, std::ifstream::in);

	if (!file.is_open())
	{
		std::cout << "Level reading error. Unable to load level: " + level_name + "\r\n";
		return;
	}

	char c;
	unsigned short arrayIndex = 0;
	unsigned short mapPickups = 0;

	while (file.good())
	{
		c = file.get();
		if (c < '0' || c > '9')
			continue;

		if (c == '2')
			mapPickups++;

		this->scene[arrayIndex % HEIGHT][arrayIndex / WIDTH] = (int)(c - '0');
		++arrayIndex;
	}

	file.close();

	if (shouldPlacePickups)
    {
    	placePickups(PICKUPS - mapPickups);
        placeSpecialPickups();
    }
}

void LevelScene::clearLevel()
{
	for (int i = 0; i < WIDTH; ++i)
    {
        for (int j = 0; j < HEIGHT; ++j)
        {
            if (this->scene[i][j] == 2 || this->scene[i][j] == -1 || this->scene[i][j] == -2)
            {
				this->scene[i][j] = 1;
            }
        }
    }
    this->scene[(WIDTH-1)/2][0] = 0;
}

void LevelScene::placePickups(int count)
{
	int loopCounter = 0;
	while (count > 0 && loopCounter < 1000000)
	{
		const int x = rand() % WIDTH;
		const int y = rand() % WIDTH;
		if (this->scene[y][x] == 1)
		{
			this->scene[y][x] = 2;
			count--;
		}

		++loopCounter;
	}
}

void LevelScene::placeSpecialPickups(int count)
{
    int loopCounter = 0;
    while (count > 0 && loopCounter < 1000000)
    {
        const int x = rand() % WIDTH;
        const int y = rand() % WIDTH;
        if (this->scene[y][x] == 1)
        {
            this->scene[y][x] = 3;
            count--;
        }

        ++loopCounter;
    }
}

void LevelScene::specialEffect()
{
    const int effectsCount = 6; //How many different effects are we currently supporting
    int effect = rand() % effectsCount;

    switch (effect)
    {
        case 0: //Walls disappear
        {
            for (int i = 1; i < WIDTH - 1; ++i)
                for (int j = 1; j < HEIGHT - 1; ++j)
                    if (this->scene[i][j] == 0)
                        this->scene[i][j] = 1;
        }
        break;
        case 1: //Make the snake shorter
        {
                this->snake->resetSize();
        }
        break;
        case 2: //Reset timer
        {
            this->restartTimer();
        }
        break;
        case 3: //Increment snake speed
        {
            if (this->snakeSpeed - 2 > 4)
                this->snakeSpeed -= 2;
        }
        break;
        case 4: //Decrement snake speed
        {
            if (this->snakeSpeed + 2 < 16)
                this->snakeSpeed += 2;
        }
        break;
        case 5: //Give some bouns points
        {
            this->score += 20;
        }
        break;
        default:
        break;
    }

    static sf::SoundBuffer buffer;
    static sf::Sound sound;
    if (!buffer.getSampleCount())
    {
        buffer.loadFromFile("assets/sounds/bouns_pickup.wav");
        sound.setBuffer(buffer);
    }
        
    sound.play();
}

void LevelScene::saveTheHighestCompletedLvl(int lvl) {
	std::ifstream lvlFileI("levels/lvlSave.lvl");
	std::stringstream ss;
	ss << lvlFileI.rdbuf();
	std::string lvlString = ss.str();
	lvlFileI.close();

	if (lvlString != ""){
		if (std::stoi(lvlString) < lvl) {
			std::ofstream lvlFileO("levels/lvlSave.lvl");
			if (lvlFileO.is_open()) {
				if (lvl == 30) {
					lvlFileO << 29;
				}
				else
					lvlFileO << lvl;
				lvlFileO.close();
			}
			else
				std::cout << "Unable to open file" << std::endl;
		}
	}
	else {
		std::ofstream lvlFileO("levels/lvlSave.lvl");
		if (lvlFileO.is_open()) {
			lvlFileO << 1;
			lvlFileO.close();
		}
		else
			std::cout << "Unable to open file" << std::endl;
	}
}
