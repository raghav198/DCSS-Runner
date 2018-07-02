#include "Point.h"


void move(Point& p, direction d)
{
	switch (d)
	{
	case NORTH:
		if (p.y > 0) p.y--;
		break;
	case SOUTH:
		p.y++;
		break;
	case EAST:
		p.x++;
		break;
	case WEST:
		if (p.x > 0) p.x--;
		break;
	case NORTHEAST:
		move(p, NORTH);
		move(p, EAST);
		break;
	case NORTHWEST:
		move(p, NORTH);
		move(p, WEST);
		break;
	case SOUTHEAST:
		move(p, SOUTH);
		move(p, EAST);
		break;
	case SOUTHWEST:
		move(p, SOUTH);
		move(p, WEST);
		break;
	default:
		break;
	}
}
