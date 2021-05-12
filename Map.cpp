// Map.cpp
#include "Route.h"
#include "City.h"
#include "Map.h"
#include "Road.h"
#include "helper.h"
#include <string>
#include <vector>
#include <map>

using namespace Orienteering;
using namespace std;

int lookupCity(City c, vector<City> cities)
{
	for (int i = 0; i < cities.size(); i++)
	{
		if (cities[i] == c)
			return i;
	}
	return -1;
}

Map::Map(vector<City> cities, vector<Road> roads)
{
	this->cities = cities;
	this->roads = roads;
	const int numVertices = cities.size();
	this->adjacency = new double* [numVertices];
	for (int i = 0; i < numVertices; i++) 
	{
		adjacency[i] = new double[numVertices];
		for (int j = 0; j < numVertices; j++)
		{
			adjacency[i][j] = 0;
		}

	}
	for (int i = 0; i < roads.size(); i++)
	{	
		Road r = roads[i];
		int first = lookupCity(r.start, cities);
		int last = lookupCity(r.end, cities);
		adjacency[first][last] = r.time;
		adjacency[last][first] = r.time;
	}
	

}


bool Map::check_cities()
{
	for (int i = 0; i < cities.size(); i++)
	{
		if (cities[i].prize < 0)
			return false;
		if ((cities[i].x > 1000) || (cities[i].x < -1000))
			return false;
		if ((cities[i].y > 1000) || (cities[i].y < -1000))
			return false;
		
		for (int j = i + 1; j < cities.size(); j++)
			if ((cities[i].x == cities[j].x) && (cities[i].y == cities[j].y))
				return false;
	}
	return true;
}

int area(int x1, int y1, int x2, int y2, int x3, int y3)
{
	return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
}

bool intersect1D(int a1, int b1, int a2, int b2)
{
	if (a1 > b1)
	{
		swap(a1, b1);
	}

	if (a2 > b2)
	{
		swap(a2, b2);
	}
	return (max(a1, a2) <= min(b1, b2));
}

bool intersect(Road e1, Road e2)
{
	if ((e1.start == e2.start) || (e1.start == e2.end))
	{
		return false;
	}
	if ((e1.end == e2.start) || (e1.end == e2.end))
	{
		return false;
	}
	int x1 = e1.start.x, y1 =  e1.start.y;
	int x2 = e1.end.x, y2 = e1.end.y;
	int x3 = e2.start.x, y3 =  e2.start.y;
	int x4 = e2.end.x, y4 = e2.end.y;
	return intersect1D(x1, x2, x3, x4) && intersect1D(y1, y2, y3, y4) && (area(x1, y1, x2, y2, x3, y3) * area(x1, y1, x2, y2, x4, y4) <= 0) && (area(x3, y3, x4, y4, x1, y1) * area(x3, y3, x4, y4, x2, y2) <= 0);
}

bool Map::check_roads()
{
	for (int i = 0; i < roads.size(); i++)
	{
		if (roads[i].time <= 0)
		{
			return false;
		}
		if (find(cities.begin(), cities.end(), roads[i].start) == cities.end())
		{
			return false;
		}
		if (find(cities.begin(), cities.end(), roads[i].end) == cities.end())
		{
			return false;
		}
		for (int j = i + 1; j < roads.size(); j++)
		{
			if (!(intersect(roads[i], roads[j])))
			{
				return false; 
			}
		}

	}
	return true;
}

bool Map::check(double time)
{
	return (time < 0) && (check_cities()) && (check_roads()) && (cities.size() > 0);
}




