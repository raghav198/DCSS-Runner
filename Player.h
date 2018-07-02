#pragma once
#include "Point.h"
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
	std::vector<Player&> summons;
	brand type;
public:

	Player(int maxHP, int maxMP, int regen, int recovery, int AC, int EV, int dmg, int (&res)[NUM_RESIST]):
		maxHP(maxHP),
		HP(maxHP),
		maxMP(maxMP),
		MP(maxMP),
		regen(regen),
		recovery(recovery),
		AC(AC),
		EV(EV),
		dmg(dmg),
		resistances(res) { }

	int HP, MP;
	Point location;
	bool move(direction);
	bool attack(Player&);
	bool takeTurn();


};

