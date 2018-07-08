#pragma once
#include "Point.h"
#include "scheduling.h"
#include "Controller.h"
#include<bitset>
#include<vector>

enum resists {
	FIRE,
	COLD,
	NEGATIVE,
	POIS,
	ELEC,
	NUM_RESIST
};

enum brand {
	FLAME,
	FREEZE,
	VAMP,
	CHAOS,
	VENOM,
	NUM_BRANDS
};

class Player
{
private:
	int maxHP;
	int maxMP;
	int regen;
	int recovery;
	int AC, EV, dmg;
	int HD;
	int (&resistances)[NUM_RESIST];
	int time;
	
	std::vector<Player*> summons;
	brand type;
	
public:

	Player(std::string name, int maxHP, int maxMP, int regen, int recovery, int AC, int EV, int dmg, int HD, int (&res)[NUM_RESIST]):
		name(name),
		maxHP(maxHP),
		HP(maxHP),
		maxMP(maxMP),
		MP(maxMP),
		regen(regen),
		recovery(recovery),
		AC(AC),
		EV(EV),
		dmg(dmg),
		resistances(res),
		time(0),
		speed(10),
		HD(HD) { }
	bool move(direction);
	bool attack(Player&);
	int takeTurn(turn);
public:
	int HP, MP;
	int speed;
	std::string name;
	Point location;
	Controller ai;
	

	int heal();
	void scheduleHeal();
};

