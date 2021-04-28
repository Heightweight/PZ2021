#pragma once
#include "City.h"
#include <string>
namespace Orienteering
{
	class Road
	{
	public:
		City start;
		City end;
		double time;
		Road(City start, City end, double time);
	};
}
