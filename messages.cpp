#include "messages.h"
#include<iostream>
#include<Windows.h>
msglog msglog::operator<<(std::string message)
{
	message.resize(this->width);
	unsigned i;
	for (i = 0; i < this->lines.size() - 1; i++)
		this->lines[i] = this->lines[i + 1];
	this->lines[i] = message;
	this->show();
	return *this;
}

void msglog::show()
{
	COORD logPos = { this->x, this->y };
	std::string blank = " ";
	blank.resize(this->width, ' ');
	// clear current set of messages
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), logPos);
	for (unsigned i = 0; i < this->lines.size(); i++)
		std::cout << blank << std::endl;
	// write out new messages
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), logPos);
	for (unsigned i = 0; i < this->lines.size(); i++)
		std::cout << this->lines[i] << std::endl;
}

msglog messages(20, 10, 50);