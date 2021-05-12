// Route.cpp

#include "Route.h"
#include "City.h"
#include "Map.h"
#include "Road.h"
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>

using namespace Orienteering;
using namespace std;

City lookupCityByName(string name, vector<City> cities)
{
	City c = City();
	for (int i = 0; i < cities.size(); i++)
	{
		if (cities[i].c_name == name)
			return cities[i];
	}
	return c; //returns a fab if no city was found 
}

void Route::append(City c)
{
	this->cities.push_back(c);
}

double Route::time(vector<Road> roadsPassed)
{
	double t = 0;
	for (int i = 0; i < cities.size() - 1; i++)
	{
		City start = cities[i];
		City end = cities[i + 1];
		for (int j = 0; j < roadsPassed.size(); j++)
		{
			if ((roadsPassed[j].start == start && roadsPassed[j].end == end) || (roadsPassed[j].start == end && roadsPassed[j].end == start))
				t += roadsPassed[j].time;
		}
	}
	return t;
}

int Route::profit()
{
	int p = 0;
	
	for (int i = 0; i < cities.size(); i++)
	{
		p += cities[i].prize; 
	}
	return p;
}

Route::Route(vector<City> cities)
{
	this->cities = cities;
}

Route::Route(string route_file, vector<City> cities)
{
	vector<City> city_init;
	ifstream routeStream(route_file);
	string read = "";
	getline(routeStream, read); //should be "solution" 
	while (getline(routeStream, read))
	{
		stringstream str(read);
		string name;
		getline(str, name);
		City nextInQueue = lookupCityByName(name, cities);
		city_init.push_back(nextInQueue);
	}
	this->cities = city_init;
}

bool Route::operator==(Route& r)
{
	if (this->cities.size() != r.cities.size())
		return false;
	for (int i = 0; i < r.cities.size(); i++)
	{
		if (!(this->cities[i] == r.cities[i]))
			return false;
	}
	return true;
}




