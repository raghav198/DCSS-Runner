#pragma once
#include "Player.h"
#include "Map.h"
#include "Controller.h"
#include "Graphics.h"
class Game
{
private:
	std::vector<Player*> players;
	Map map;
	Graphics g;
private:
	bool turnIsValid(Player *, turn&);
public:
	Game(Map map, std::vector<Player*> players) :
		map(map),
		players(players),
		g(map, players) { }
	Game(Map map, std::vector<Player*> players, msglog log) :
		map(map),
		players(players),
		g(map, players, log) { }
	int getPlayerTurn(Player *);
	int kill(Player *);
	
	
};

