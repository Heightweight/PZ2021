#pragma once
#include "City.h"
#include "Map.h"
#include <vector>

using namespace std;
namespace Orienteering
{
	class Route {
	public:
		vector<City> cities;
		void append(City c);
		double time(Map m);
		int profit();
		Route(List<City> cities);
		Route(string route_file);
	};
}

