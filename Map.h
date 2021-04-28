#pragma once
#include "City.h"
#include "Road.h"
#include "Route.h"
#include <vector>
#include <string>

using namespace std;

namespace Orienteering
{
	class Map {
	public:
		vector<City> cities;
		vector<Road> roads;
		double** incidency;
		bool check_cities();
		void draw();
		//Route solve_h();
		bool check_roads();
		bool check(double time);
		//void show_solution(Route solution);
		//Map(string city_file, string road_file);
		//Map(vector<City> cities, vector<Road> roads);
	};
}