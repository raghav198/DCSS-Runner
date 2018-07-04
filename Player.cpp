#include "Player.h"
#include<math.h>
#include<cstdlib>


bool Player::move(direction d)
{
	Point& old(this->location);
	::move(this->location, d);
	return old.x != this->location.x && old.y != this->location.y;
}

bool Player::attack(Player& p)
{
	if (abs(this->location.x - p.location.x) > 1 || abs(this->location.y - p.location.y) > 1)
		return false; // too far away, cannot attack (no reaching!)

	// otherwise the attack proceeds. Step 1: check evasion
	int toHitMax = (int)(2.5 * this->HD); // all players are by default fighters
	int evadeMax = 2 * p.EV - 1;

	int toHitRoll = rand() % toHitMax;
	int evadeRoll = rand() % evadeMax;

	if (evadeRoll > toHitRoll)
		return true; // the target successfully evaded

	// otherwise, the attack proceeds. Step 2: check armor
	int acRoll = rand() % p.AC;
	// not dealing with GDR
	int damage = this->dmg - acRoll;
	if (damage < 0)
		return true; // the target's armor absorbed the entire attack

	// otherwise, the attack proceeds. Step 3: check brands
	

	p.HP -= damage;
	// if (p.HP < 0) kill(&p);
	// schedule.push(p.heal());

	return true;

}

bool Player::takeTurn()
{
	// TODO: manav implements this piece
	return false;
}
