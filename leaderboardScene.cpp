#include "leaderboardScene.h"

LeaderboardScene::LeaderboardScene(sf::RenderWindow *window, sf::Event *event, AssetManager *manager)
{
    asset_manager = manager;
    this->window = window;
    this->event = event;
    next_scene = none;

    this->topPlayers = this->getLeaderboard();
}

LeaderboardScene::~LeaderboardScene() { }

void LeaderboardScene::handleInput()
{
    while (window->pollEvent(*event))
    {
        //This should be handled everywhere
        if (event->type == sf::Event::Closed)
        {
            next_scene = quit;
        }

        if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Escape)
        {
            next_scene = main_menu;
        }
    }
}

void LeaderboardScene::handleLogic()
{

}

void LeaderboardScene::handleRender()
{
    window->clear();

    //Background
    background.setSize((sf::Vector2f)window->getSize());
    background.setTexture(asset_manager->getTexture("assets/background.png"));
    window->draw(background);

    //Title
    sf::Text text("Leaderboards", *asset_manager->getFont());
    text.setCharacterSize(70);
    text.setPosition(WINDOW_WIDTH / 2 - text.getGlobalBounds().width / 2, 10);
    text.setColor(sf::Color(60, 0, 0, 255));
    window->draw(text);

    //Leaderboards
    text.setColor(sf::Color(140, 10, 10, 255));

    short i = 0;
    for (std::vector<std::string>::iterator it = this->topPlayers.begin(); it != this->topPlayers.end(); ++it)
    {
        if (i == 0) //First place
        {
            text.setString(*it);
            text.setCharacterSize(60);
            text.setPosition(WINDOW_WIDTH / 2 - text.getGlobalBounds().width / 2, 110);
            window->draw(text);

            //Set font size for other results
            text.setCharacterSize(30);
            ++i;
            continue;
        }

        text.setString(*it);
        text.setPosition(WINDOW_WIDTH / 2 - text.getGlobalBounds().width / 2, i * 50 + 150);
        window->draw(text);

        ++i;
    }

    window->display();
}

std::vector<std::string> LeaderboardScene::getLeaderboard(std::string filename)
{
    std::vector<std::string> vec;
    std::ifstream file;
    file.open("data/" + filename, std::ifstream::in);

    if (!file.is_open())
    {
        std::cout << "File read error. Unable to load leaderboard\r\n";
        return vec;
    }

    std::string buff;

    while (file.good())
    {
        std::getline(file, buff, '\n');

        if (buff.length() == 0)
            continue;

        std::size_t pos = buff.find_first_of(";");
        buff.replace(pos, 1, " - ");
        vec.push_back(buff);
    }

    file.close();

    return vec;
}
