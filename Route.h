#pragma once
#include "City.h"
#include "Road.h"
#include <vector>

using namespace std;

namespace Orienteering
{
	class Route {
	public:
		vector<City> cities;
		void append(City c);
		double time(vector<Road> roads);
		int profit();
		Route(vector<City> cities);
		Route(string route_file, vector<City> cities);
		bool operator==(Route& c);
	};
}

