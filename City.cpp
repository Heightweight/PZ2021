// City.cpp
#include "City.h"
#include <string>

using namespace Orienteering;

City::City(int x, int y, int prize, string name)
{
	this->x = x;
	this->y = y;
	this->prize = prize;
	this->name = name;
}