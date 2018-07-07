#include "Player.h"
#include<math.h>
#include<cstdlib>
#include<future>
#include<iostream>

extern scheduler sched;

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
	std::cout << "Checking evade (" << toHitRoll << " vs " << evadeRoll << ")\n";
	if (evadeRoll > toHitRoll)
		return true; // the target successfully evaded

	// otherwise, the attack proceeds. Step 2: check armor
	int acRoll = rand() % p.AC;
	// not dealing with GDR
	int damage = this->dmg - acRoll;
	std::cout << "Armor reduced damage to " << damage << "\n";
	if (damage < 0)
		return true; // the target's armor absorbed the entire attack

	// otherwise, the attack proceeds. Step 3: check brands
	

	p.HP -= damage;
	p.scheduleHeal();
	
	// if (p.HP < 0) kill(&p);
	// schedule.push(p.heal());

	task nextTurn = { std::async(std::launch::deferred, &Player::takeTurn, this), sched.cur_time + this->speed };
	sched.schedule(nextTurn);
	

	return true;

}

int Player::takeTurn()
{
	// TODO: manav implements this piece
	return 0;
}

void Player::scheduleHeal()
{
	int nextTime = this->recovery + sched.cur_time;
	task nextHeal = { std::async(std::launch::deferred, &Player::heal, this), nextTime };
	sched.schedule(nextHeal);
	std::cout << "Scheduled a heal for time t=" << nextTime << std::endl;
}

int Player::heal()
{
	this->HP++;
	std::cout << "The time is " << sched.cur_time << " and " << this->name << " just healed to " << this->HP << " HP\n";
	if (this->HP < this->maxHP)
	{
		std::cout << "More healing is left to do!\n";
		this->scheduleHeal();
	}
		

	return 0;
}
