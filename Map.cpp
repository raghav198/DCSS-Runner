#include "Map.h"
#include<random>
Map::Map(int x, int y)
{
	this->size = Point(x, y);
	this->map = new tile[x * y];
}

tile Map::at(int x, int y)
{
	if (x < 0 || y < 0) return NUM_TILES;
	if (x > this->size.x || y > this->size.y) return NUM_TILES;
	return this->map[x * this->size.x + y];
}

void Map::make(float WALL_CHANCE, float WATER_CHANCE)
{
	int sz = this->size.x;
	for (int i = 0; i < this->size.y; i++)
	{
		for (int j = 0; j < this->size.x; j++)
		{
			double x = ((double)rand() / (double)RAND_MAX);
			if (x < WALL_CHANCE) this->map[i * sz + j] = WALL;
			else if (x < WATER_CHANCE) this->map[i * sz + j] = WATER;
			else this->map[i * sz + j] = BLANK;
		}
	}
}

void Map::makeBlank()
{
	int sz = this->size.x;
	this->make(0, 0);
	// left and right borders
	for (int i = 0; i < this->size.y; i++)
	{
		this->map[i * sz] = WALL;
		this->map[(i + 1) * sz - 1] = WALL;
	}
	// top and bottom borders
	for (int i = 0; i < sz; i++)
	{
		this->map[i] = WALL;
		this->map[sz * (this->size.y - 1) + i] = WALL;
	}
}