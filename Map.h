#include "Point.h"
#pragma once
enum tile {
	BLANK,
	WALL,
	WATER,
	NUM_TILES
};

class Map {
private:
	tile * map;
public:
	Point size;
public:
	Map(int x, int y);
	tile at(int, int);
	void make(float wall, float water);
	void makeBlank();
};