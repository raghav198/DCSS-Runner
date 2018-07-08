#include "Game.h"
#include "scheduling.h"
#include<future>

extern scheduler sched;

bool Game::turnIsValid(Player * p, turn& t)
{
	Point dest;
	if (t.type == MOVE || t.type == ATTACK)
	{
		Point dir;
		switch (t.dir)
		{
		case NORTH:
			dir = { 0, -1 };
			break;
		case SOUTH:
			dir = { 0, 1 };
			break;
		case EAST:
			dir = { 1, 0 };
			break;
		case WEST:
			dir = { -1, 0 };
			break;
		default:
			dir = { 0, 0 };
			break;
		}
		dest = p->location + dir;
	}
	else
	{
		dest = t.dest;
	}
	if (map.at(dest.x, dest.y) == NUM_TILES)
		return false;
	else if (map.at(dest.x, dest.y) == WALL)
		return false;

	for (Player * p : this->players)
	{
		if (p->location == dest)
		{
			t.type = ATTACK;
			t.target = p;
			break;
		}
	}

	return true;
}

int Game::getPlayerTurn(Player * p)
{
	this->g.showMap();
	this->g.showStatus(*p);
	turn t(NUM_TURNS, NUM_DIRS);
	while (!this->turnIsValid(p, t = p->ai.readPlayerTurn()));
	// at the end of this while loop, t is guaranteed to have a valid turn
	int turnLength = p->speed;
	int nextTurn = turnLength + sched.cur_time;
	task next = { std::async(std::launch::deferred, &Game::getPlayerTurn, *this, p), nextTurn };
	sched.schedule(next);
	p->takeTurn(t);
	return 0;
}

