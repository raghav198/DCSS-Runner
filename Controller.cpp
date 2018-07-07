#include "Controller.h"
#include<conio.h>
turn Controller::getPlayerTurn()
{
	int c;
	while (c = _getwch())
	{
		if (c == 0x0E)
		{
			c <<= 8;
			c += _getwch();
		}

		switch (c)
		{
		case 0x0E48:
			return turn(MOVE, NORTH);
		case 0x0E50:
			return turn(MOVE, SOUTH);
		case 0x0E4D:
			return turn(MOVE, EAST);
		case 0x0E4B:
			return turn(MOVE, WEST);
		}

	}
	return turn(NUM_TURNS, NUM_DIRS); // default (something bad happened)
	
}
