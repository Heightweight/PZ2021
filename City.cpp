// City.cpp
#include "City.h"
#include <string>

using namespace Orienteering;
using namespace std;

City::City(double x, double y, int prize, string name)
{
	this->x = x;
	this->y = y;
	this->prize = prize;
	this->c_name = name;
}

bool City::operator==(City c)
{
	return (this->x == c.x) && (this->y == c.y) && (this->prize == c.prize) && (this->c_name == c.c_name);
}
