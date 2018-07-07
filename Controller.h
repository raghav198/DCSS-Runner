#pragma once
#include "Player.h"
#include "Point.h"
enum turn_type {
	ATTACK,
	MOVE,
	NUM_TURNS
};

struct turn {
	turn_type type;
	union {
		Point dest;
		direction dir;
	};
	turn(turn_type t, Point d) :
		type(t),
		dest(d) { }
	turn(turn_type t, direction d) :
		type(t),
		dir(d) { }
};

class Controller
{
public:
	Controller(Player p) :
		player(p) { }
	turn getPlayerTurn();
private:
	Player player;
};

