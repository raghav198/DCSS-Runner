#include<array>
#include<string>

struct msglog {
	msglog(int w, short x, short y) :
		width(w),
		x(x),
		y(y) { }
	std::array<std::string, 5> lines;
	int width;
	short x, y;
	msglog operator<<(std::string);
	void show();
}; 

