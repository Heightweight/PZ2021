#pragma once
#include "City.h"
#include "Map.h"
#include <vector>
#include <string>

using namespace std;

namespace Orienteering
{
	class Route {
	public:
		vector<City> cities;
		void append(City c);
		double time(Map m);
		int profit();
		//Route(vector<City> cities);
		//Route(string route_file);
	};
}

