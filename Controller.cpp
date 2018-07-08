#include "Controller.h"
#include<conio.h>
turn Controller::readArrowTurn()
{
	int c;
	while (c = _getwch())
	{
		if (c == 0xE0)
		{
			c <<= 8;
			c += _getwch();
		}

		switch (c)
		{
		case 0xE048:
			return turn(MOVE, NORTH);
		case 0xE050:
			return turn(MOVE, SOUTH);
		case 0xE04D:
			return turn(MOVE, EAST);
		case 0xE04B:
			return turn(MOVE, WEST);
		}

	}
	return turn(NUM_TURNS, NUM_DIRS); // default (something bad happened)
	
}

turn Controller::readWASDTurn()
{
	int c;
	while (c = _getwch())
	{
		if (c == 0xE0)
		{
			c <<= 8;
			c += _getwch();
		}

		switch (c)
		{
		case 'w':
			return turn(MOVE, NORTH);
		case 's':
			return turn(MOVE, SOUTH);
		case 'd':
			return turn(MOVE, EAST);
		case 'a':
			return turn(MOVE, WEST);
		}

	}
	return turn(NUM_TURNS, NUM_DIRS); // default (something bad happened)

}

turn Controller::readPlayerTurn()
{
	switch (this->type)
	{
	case NUM_CTRLS:
		return turn(NUM_TURNS, NUM_DIRS);
	case CTRL_ARROW:
		return this->readArrowTurn();
	case CTRL_WASD:
		return this->readWASDTurn();
	}
}
