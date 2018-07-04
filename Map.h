#include "Point.h"

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
	~Map();
	tile at(int, int);
};