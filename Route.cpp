// Route.cpp
#include "Route.h"
#include "City.h"
#include "Road.h"
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>

using namespace Orienteering;
using namespace std;

City lookupCityRByName(string name, vector<City> cities)
{
	City c = City();
	for (int i = 0; i < cities.size(); ++i)
	{
		if (cities[i].c_name == name)
			return cities[i];
	}
	return c; //returns a fab if no city was found 
}

inline void Route::append(City &c)
{
	this->cities.push_back(c);
}

inline double Route::time(double** &adjacency)
{
	double t = 0;
	for (int i = 0; i < (int)this->cities.size() - 1; ++i)
	{
		City start = this->cities[i];
		City end = this->cities[i + 1];
		t += adjacency[start.nubmerAssigned][end.nubmerAssigned];
	}
	return t;
}

inline int Route::profit()
{
	int p = 0;
	vector<City> visited;
	for (int i = 0; i < cities.size(); ++i)
	{
		if (find(visited.begin(), visited.end(), cities[i]) == visited.end())
		{
			p += cities[i].prize;
			visited.push_back(cities[i]);
		}
		
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
		string nm;
		getline(str, nm);
		City nextInQueue = lookupCityRByName(nm, cities);
		city_init.push_back(nextInQueue);
	}
	this->cities = city_init;
}

bool Route::operator==(Route& r)
{
	if (this->cities.size() != r.cities.size())
		return false;
	for (int i = 0; i < r.cities.size(); ++i)
	{
		if (!(this->cities[i] == r.cities[i]))
			return false;
	}
	return true;
}




