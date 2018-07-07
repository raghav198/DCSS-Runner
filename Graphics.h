#pragma once
#include "Map.h"
#include "Player.h"
#include<string>
#include<vector>
#include<array>

struct msglog {
	msglog(int w, short x, short y) :
		width(w),
		x(x),
		y(y) { }
	std::array<std::string, 5> lines;
	int width;
	short x, y;
};

class Graphics
{
private:
	Map map;
	msglog messages;
	std::vector<Player> players;
	void fillMap();
	void addPlayers();
	void showLog();
public:
	Graphics(Map map, std::vector<Player> players) :
		map(map),
		players(players),
		messages(20, 10, 50) { }
	~Graphics();
	void log(std::string);
	void showMap();
};

