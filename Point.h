
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
	int x, y;
	Point() = default;
	Point(int x, int y) : 
		x(x), 
		y(y) { }
};

void move(Point&, direction);