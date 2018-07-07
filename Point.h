#pragma once
enum direction {
	NORTH,
	SOUTH,
	EAST,
	WEST,
	NORTHEAST,
	NORTHWEST,
	SOUTHEAST,
	SOUTHWEST,
	NUM_DIRS
};

struct Point {
	short x, y;
	Point() = default;
	Point(short x, short y) : 
		x(x), 
		y(y) { }
};

void move(Point&, direction);