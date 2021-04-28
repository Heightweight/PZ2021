// City.cpp
#include "City.h"
#include <string>

using namespace Orienteering;

City::City(int x, int y, int prize, string c_name)
{
	this->x = x;
	this->y = y;
	this->prize = prize;
	this->c_name = c_name;
}

City::City()
{
	this->x = 0;
	this->y = 0;
	this->prize = 0;
	this->c_name = "";
}

bool City::operator==(City c)
{
	return ((this->x == c.x) && (this->y == c.y) && (this->prize == c.prize) && (this->c_name == c.c_name));
}