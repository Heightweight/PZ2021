// Road.cpp
#include "City.h"
#include <string>
#include "Road.h"

using namespace Orienteering;

Road::Road(City start, City end, double time)
{
	this->start = start;
	this->end = end;
	this->time = time;

}

