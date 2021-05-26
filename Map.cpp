// Map.cpp
#include "Route.h"
#include "City.h"
#include "Map.h"
#include "Road.h"
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <map>


using namespace Orienteering;
using namespace std;

int lookupCity(City c, vector<City> cities)
{
	for (int i = 0; i < cities.size(); ++i)
	{
		if (cities[i] == c)
			return i;
	}
	return -1;
}

City lookupCityByName(string name, vector<City> cities)
{
	City c = City();
	for (int i = 0; i < cities.size(); ++i)
	{
		if (cities[i].c_name == name)
			return cities[i];
	}
	return c; //returns a fab if no city was found 
}

Map::Map(vector<City> cities, vector<Road> roads)
{
	this->cities = cities;
	this->roads = roads;
	map<int, vector<int>> dFN;
	const int numVertices = cities.size();
	this->adjacency = new double* [numVertices];
	for (int i = 0; i < numVertices; ++i)
	{
		adjacency[i] = new double[numVertices];
		this->cities[i].nubmerAssigned = i;
		dFN[i] = {};
		for (int j = 0; j < numVertices; ++j)
		{
			adjacency[i][j] = 0;
		}

	}
	for (int i = 0; i < roads.size(); ++i)
	{	
		Road r = roads[i];
		int first = lookupCity(r.start, cities);
		int last = lookupCity(r.end, cities);
		adjacency[first][last] = r.time;
		adjacency[last][first] = r.time;
		dFN[first].push_back(last);
	}
	for (int i = 0; i < cities.size(); ++i)
	{
		indexName[cities[i].c_name] = i;
	}
	this->deltaFromNumber = dFN;
}

Map::Map(string city_file, string road_file)
{
	vector<City> city_init;
	vector<Road> road_init;
	ifstream cityStream(city_file);
	string read = "";
	getline(cityStream, read);
	int j = 0;
	while (getline(cityStream, read))
	{
		stringstream str(read);
		string data[4];
		for (int i = 0; i < 4; ++i)
		{
			getline(str, data[i], ',');
		}
		string name = data[0];
		double x = stod(data[1]);
		double y = stod(data[2]);
		int prize = stoi(data[3]);
		City nextInQueue = City(x, y, prize, name);
		nextInQueue.nubmerAssigned = j;
		city_init.push_back(nextInQueue);
		++j;

	}
	ifstream roadStream(road_file);
	read = "";
	getline(roadStream, read);
	while (getline(roadStream, read))
	{
		stringstream str(read);
		string data[3];
		for (int i = 0; i < 3; ++i)
		{
			getline(str, data[i], ',');
		}
		City start = lookupCityByName(data[0], city_init);
		City end = lookupCityByName(data[1], city_init);
		Road nextInQueue = Road(start, end, stod(data[2]));
		Road nextInQueue2 = Road(end, start, stod(data[2]));
		road_init.push_back(nextInQueue);
		road_init.push_back(nextInQueue2);
	}

	this->cities = city_init;
	this->roads = road_init;
	this->adjacency = Map(city_init, road_init).adjacency;
	this->deltaFromNumber = Map(city_init, road_init).deltaFromNumber;
}

bool Map::check_cities()
{
	for (int i = 0; i < cities.size(); ++i)
	{
		if (cities[i].prize < 0)
			return false;
		if ((cities[i].x > 1000) || (cities[i].x < -1000))
			return false;
		if ((cities[i].y > 1000) || (cities[i].y < -1000))
			return false;
		
		for (int j = i + 1; j < cities.size(); ++j)
			if ((cities[i].x == cities[j].x) && (cities[i].y == cities[j].y))
				return false;
	}
	return true;
}

double area(double x1, double y1, double x2, double y2, double  x3, double y3)
{
	return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
}

bool intersect1D(double a1, double b1, double a2, double b2)
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
	if ((e1.start == e2.end) && (e1.end == e2.start))
	{
		if (e1.time == e2.time)
			return false;
		else
			return true;
	}
	if ((e1.start == e2.start) && (e1.end == e2.end))
	{
		return true;
	}
	if ((e1.start == e2.end) && (e1.end == e2.start))
	{
		return true;
	}
	if ((e1.start == e2.start) || (e1.start == e2.end))
	{
		return false;
	}
	if ((e1.end == e2.start) || (e1.end == e2.end))
	{
		return false;
	}
	double x1 = e1.start.x, y1 =  e1.start.y;
	double x2 = e1.end.x, y2 = e1.end.y;
	double x3 = e2.start.x, y3 =  e2.start.y;
	double x4 = e2.end.x, y4 = e2.end.y;
	return intersect1D(x1, x2, x3, x4) && intersect1D(y1, y2, y3, y4) && (area(x1, y1, x2, y2, x3, y3) * area(x1, y1, x2, y2, x4, y4) <= 0) && (area(x3, y3, x4, y4, x1, y1) * area(x3, y3, x4, y4, x2, y2) <= 0);
}

bool Map::check_roads()
{
	for (int i = 0; i < roads.size(); ++i)
	{
		if (roads[i].start == roads[i].end)
		{
			return false;
		}
		
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
		
		for (int j = i + 1; j < roads.size(); ++j)
		{
			if (intersect(roads[i], roads[j]))
			{
				return false; 
			}
		}

	}
	return true;
}

bool Map::check(double time)
{
	return (time >= 0) && (check_cities()) && (check_roads()) && (cities.size() > 0);
}

Route Map::solve_e(double time)
{
	

		Route emptyRoute = Route(vector<City>()); //empty route with no cities
		vector<Route> r_old;
		r_old.push_back(emptyRoute);
		vector<Route> r_new;
		Route max_route = emptyRoute;
		int max_profit = -1;
		int t_max = time;
		int length = this->cities.size();
		vector<City> cities = this->cities;
		while (r_old.size() != 0)
		{
			for (int i = 0; i < r_old.size(); ++i)
			{
				for (int j = 0; j < length; ++j)
				{
					Route toModify = r_old[i];
					City end = toModify.cities.back();
					City toAppend = cities[j];
					int numberEnd = lookupCity(end, cities);
					int numberToAppend = lookupCity(toAppend, cities);
					if (adjacency[numberToAppend][numberEnd] > 0 && toModify.time(this->adjacency) + this->adjacency[numberToAppend][numberEnd] <= time)
					{
						toModify.append(toAppend);
						r_old.push_back(toModify);
						if (toModify.profit() > max_profit)
						{
							max_profit = toModify.profit();
							max_route = toModify;
						}
					}

				}
			}
			r_old = r_new;
			r_new.clear();

		}
		return max_route;
}

double weight(int& j, int& i, Map& m)
{
	if (m.adjacency[i][j] != 0)
		return pow((m.cities[i].prize), 2) / pow(m.adjacency[i][j], 3);

	return -1; 
}

vector<int> delta(int &cityNumber, Route &route, Map &m, double &time)
{
	vector<int> delta; //empty init
	vector<int> deltaUnfiltered = m.deltaFromNumber[cityNumber];
	int length = deltaUnfiltered.size();
	double t = route.timeCurrent;
	for (int i = 0; i < length; ++i) //cycling through all cities
	{
		if (t+m.adjacency[cityNumber][deltaUnfiltered[i]]<time)
			delta.push_back(deltaUnfiltered[i]);
	}
	return delta; //returns all acceptable adjacent cities to cityNumber

}

Route next_r(Map &m, Route &r, double &time)
{
	int endCity = r.cities.back().nubmerAssigned;
	vector<int> city_delta = delta(endCity, r, m, time);

	if (city_delta.size() != 0)
	{	
		int n = city_delta.size();
		vector<double> weights;
		for (int i = 0; i < n; ++i)
		{
			double w = weight(endCity, city_delta[i], m);
			for (int j = 0; j < r.cities.size(); ++j)
			{
				if (city_delta[i] == r.cities[j].nubmerAssigned)
				{
					w = 0;
					break;
				}
			}
			weights.push_back(w);
		}
		for (int i = 0; i < n; ++i)
		{
			for (int j = i + 1; j < n; ++j)
			{
				if (weights[i] < weights[j])
				{
					swap(weights[i], weights[j]);
					swap(city_delta[i], city_delta[j]);

				}
			}
		} //sorting weights and delta at the same time

		vector<double> max_3(weights.begin(), weights.begin() + min(3, (int)weights.size()));
		double sum = 0;
		for (vector<double>::iterator it = max_3.begin(); it != max_3.end(); ++it)
		{
			sum += *it;
		}
		if (sum > 0)
		{
			for (int i = 0; i < max_3.size(); ++i)
				max_3[i] /= sum;
		}
		else
			for (int i = 0; i < max_3.size(); ++i)
				max_3[i] = (1 / max_3.size());


		double probability = ((rand() % 100) + 1) / 100;
		double accum = 0;
		int randomized = 0;
		for (int i = 0; i < max_3.size(); ++i)
		{
			if (probability > accum && probability <= accum + max_3[i])
			{
				randomized = i;
				break;
			}
			accum += max_3[i];
		}
		/*Route copy = r;
		copy.append(m.cities[city_delta[randomized]]);
		if (copy.time(m.roads) <= time)
		{
			
		}*/
		r.append(m.cities[city_delta[randomized]]);
		r.timeCurrent += m.adjacency[city_delta[randomized]][endCity];
		return r;
	}
	 
	return r;
}

Route Map::solve_h(double &time)
{
	Route r_max = Route(vector<City>());
	int max_profit = -1;
	for (int i = 0; i < cities.size(); ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			Route newRoute = Route(vector<City>());
			Route r_old = newRoute;		
			newRoute.append(this->cities[i]);
			Route r_new = newRoute;
			r_old.timeCurrent = 0;
			r_new.timeCurrent = 0;
			do
			{
				r_old = r_new;
				r_new = next_r(*this, r_new, time);
			} while (!(r_new.cities.back() == r_old.cities.back()));
			int r = r_new.profit();
			if (r > max_profit)
			{
				r_max = r_new;
				max_profit = r;
			}
		}
	}
	return r_max;
}






