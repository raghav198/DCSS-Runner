#include "Map.h"

Map::Map(int x, int y)
{
	this->size = Point(x, y);
	this->map = new tile[x * y];
}

Map::~Map()
{
	delete[] this->map;
}

tile Map::at(int x, int y)
{
	return this->map[x * this->size.x + y];
}
