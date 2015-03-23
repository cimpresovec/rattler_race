#ifndef LEADERBOARDSCENE_H
#define LEADERBOARDSCENE_H

#include "gameScene.h"
#include "assetManager.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

class LeaderboardScene : public GameScene
{
private:
	std::vector<std::string> topPlayers;

public:
    LeaderboardScene(sf::RenderWindow *window, sf::Event *event, AssetManager *manager);
    virtual ~LeaderboardScene();

    void handleInput();
    void handleLogic();
    void handleRender();

    std::vector<std::string> getLeaderboard(std::string filename = "leaderboard.snek");
};

#endif // LEADERBOARDSCENE_H
