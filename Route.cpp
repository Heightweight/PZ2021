// Route.cpp

#include "Route.h"
#include "City.h"
#include "Map.h"
#include "Road.h"
#include <string>
#include <vector>

using namespace Orienteering;
using namespace std;

void Route::append(City c)
{
	this->cities.push_back(c);
}

double Route::time(Map m)
{
	cities = this->cities;
	for (i = 0; i < cities.size() - 1; i++)
	{	
		int posStart = -1;
		int posEnd = -1;
		double t = 0;
		for (j = 0; j < m.cities.size(); j++)
		{
			if (m.cities[j] == cities[i])
			{
				posStart = j;
			}
			if (m.cities[j] == cities[i + 1])
			{
				posEnd = j;
			}
		}
		t = t + m.incidency[posStart][posEnd];
		return t;
	}
}

int Route::profit()
{
	int p = 0;
	
	for (i = 0; i < cities.size(); i++)
	{
		p += cities[i].prize; 
	}
	return p;
}




