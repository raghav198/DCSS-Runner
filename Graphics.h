#pragma once
#include "Map.h"
#include "Player.h"
#include "messages.h"
#include<string>
#include<vector>
#include<array>


class Graphics
{
private:
	Map map;
	msglog messages;
	std::vector<Player*> players;
	void fillMap();
	void addPlayers();
public:
	Graphics(Map map, std::vector<Player*> players) :
		map(map),
		players(players),
		messages(20, 10, 50) { }
	Graphics(Map map, std::vector<Player*> players, msglog log) :
		map(map),
		players(players),
		messages(log) { }
	void log(std::string);
	void showMap();
	void showStatus(Player);
};

