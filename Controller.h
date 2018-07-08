#pragma once

#include "Point.h"
#include "turn.h"

enum controller_type {
	CTRL_ARROW,
	CTRL_WASD,
	NUM_CTRLS
};

class Controller
{
private:
	turn readArrowTurn();
	turn readWASDTurn();
public:
	controller_type type;
public:
	Controller(controller_type t) :
		type(t) { }
	Controller() :
		type(NUM_CTRLS) { }
	turn readPlayerTurn();
};
