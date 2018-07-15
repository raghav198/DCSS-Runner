#include "Graphics.h"
#include<iostream>
#include<Windows.h>
#include "Map.h"

void Graphics::fillMap()
{
	for (int i = 0; i < this->map.size.y; i++)
	{
		for (int j = 0; j < this->map.size.x; j++)
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 2 * (short)i, (short)j });
			switch (this->map.at(i, j))
			{
			case WALL:
				std::cout << '#';
				break;
			case WATER:
				std::cout << '~';
				break;
			case BLANK:
				std::cout << ' ';
				break;
			}
		}
	}
}

void Graphics::addPlayers()
{
	for (unsigned int i = 0; i < this->players.size(); i++)
	{
		Player * p = this->players[i];
		char rep = 'A' + i;
		COORD c = *((COORD *)&(*p).location);
		c.X *= 2;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		std::cout << rep;
	}
}

void Graphics::showMap()
{
	this->fillMap();
	this->addPlayers();
}

void Graphics::showStatus(Player cur)
{
	short x = 70;
	short y = 0;
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x + 15, y });
	std::cout << "HP";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x + 20, y });
	std::cout << "MP";
	std::string blank = " ";
	blank.resize(23, ' ');
	for (Player * p : this->players)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x, ++y });
		std::cout << blank;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x, y });
		if (cur.name == p->name) std::cout << '*';
		std::cout << p->name;
		if (p->pois)
			std::cout << " pois " << p->pois;
		std::cout << ' ';
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x + 15, y });
		std::cout << p->HP;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x + 20, y });
		std::cout << p->MP;
	}
}

void Graphics::log(std::string message)
{
	this->messages << message;
	this->messages.show();
}

