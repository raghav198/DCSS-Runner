#pragma once
#include "Point.h"
class Player;
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
		Player * target;
	};
	turn(turn_type t, Point d) :
		type(t),
		dest(d) { }
	turn(turn_type t, direction d) :
		type(t),
		dir(d) { }
};
