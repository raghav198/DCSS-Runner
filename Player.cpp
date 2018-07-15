#include "Player.h"
#include "messages.h"
#include<math.h>
#include<cstdlib>
#include<future>
#include<iostream>

extern scheduler sched;
extern msglog messages;

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
	// std::cout << "Checking evade (" << toHitRoll << " vs " << evadeRoll << ")\n";
	if (evadeRoll > toHitRoll)
		return true; // the target successfully evaded

	// otherwise, the attack proceeds. Step 2: check armor
	int acRoll = rand() % p.AC;
	// not dealing with GDR
	int damage = this->dmg - acRoll;
	// std::cout << "Armor reduced damage to " << damage << "\n";
	if (damage < 0)
		return true; // the target's armor absorbed the entire attack

	// otherwise, the attack proceeds. Step 3: check brands
	brand type;
	if (this->type == CHAOS)
	{
		// do a check for chaos stuff
	}
	else type = this->type;

	int extraDamage = 0;
	switch (type) {
	case FLAME:
		extraDamage = rand() % (int)(0.5 * damage);
		if (p.resistances[FIRE] <= -1)
			extraDamage *= 1.5;
		else if (p.resistances[FIRE] == 1)
			extraDamage *= 0.5;
		else if (p.resistances[FIRE] == 2)
			extraDamage *= 0.33;
		else if (p.resistances[FIRE] == 3)
			extraDamage *= 0.2;
		messages << "Fire!!";
		break;
	case FREEZE:
		extraDamage = rand() % (int)(0.5 * damage);
		if (p.resistances[COLD] <= -1)
			extraDamage *= 1.5;
		else if (p.resistances[COLD] == 1)
			extraDamage *= 0.5;
		else if (p.resistances[COLD] == 2)
			extraDamage *= 0.33;
		else if (p.resistances[COLD] == 3)
			extraDamage *= 0.2;
		break;
	case ELECTRO:
		if (rand() % 100 <= 33) {
			extraDamage = 7 + rand() % 13;
			if (p.resistances[ELEC])
				extraDamage *= 0.25;
		}
		break;
	case VAMP:
		if (rand() % 100 <= 60)
			this->HP += rand() % damage;
		if (this->HP > this->maxHP)
			this->HP = this->maxHP;
		break;
	case HOLY:
		extraDamage = rand() * (int)(1.5 * damage);
		break;
	case VENOM:
		if (rand() % 3 < 2)
		{
			p.pois++;
			int nextTime = sched.cur_time + 10;
			task pois = { std::async(std::launch::deferred, &Player::handlePoison, &p), nextTime };
			sched.schedule(pois);
		}

	default:
		break;
		
	}

	p.HP -= damage;
	p.HP -= extraDamage;

	
	// if (p.HP < 0) kill(&p);
	// schedule.push(p.heal());
	

	return true;

}

int Player::handlePoison()
{
	if (this->pois < 0) this->pois = 0;
	int dmg = (this->pois >= 4);
	if (rand() % 2) dmg += (rand() % (this->pois + 1)) + 1;
	dmg = (int)(0.5 * dmg);

	this->HP -= dmg;

	if (rand() % (this->HD + 10) < this->HD) this->pois--;
	if (this->pois)
	{
		int nextTime = sched.cur_time + 10;
		task pois = { std::async(std::launch::deferred, &Player::handlePoison, this), nextTime };
		sched.schedule(pois);
	}

	return this->pois;
}

int Player::takeTurn(turn t)
{
	switch (t.type)
	{
	case MOVE:
		this->move(t.dir);
		break;
	case ATTACK:
		this->attack(*(t.target));
		break;
	default:
		// std::cout << "I have no idea how to take that turn\n";
		break;
	}
	return 0;
}


void Player::scheduleHeal()
{
	int nextTime = this->recovery + sched.cur_time;
	task nextHeal = { std::async(std::launch::deferred, &Player::heal, this), nextTime };
	sched.schedule(nextHeal);
	// std::cout << "Scheduled a heal for time t=" << nextTime << std::endl;
}

int Player::heal()
{
	if (this->HP < this->maxHP) this->HP++;
	// std::cout << "The time is " << sched.cur_time << " and " << this->name << " just healed to " << this->HP << " HP\n";
	this->scheduleHeal();
		

	return 0;
}
