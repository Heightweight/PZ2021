#pragma once
#include "City.h"
#include "Road.h"
#include <vector>

using namespace std;

namespace Orienteering
{
	/// <summary>
	/// Short describtion of Route class.
	/// 
	/// Class contains route of salesman.
	/// </summary>
	class Route {
	public:
		/// <summary>
		/// Vector which contains route of salesman.
		/// </summary>
		vector<City> cities;
		void append(City c);
		/// <summary>
		/// Function of route time
		/// </summary>
		/// <param name="roads">route of salesman</param>
		/// <returns>time of route</returns>
		double time(vector<Road> roads);
		/// <summary>
		/// Function of saled stock 
		/// </summary>
		/// <returns>amount of saled stock</returns>
		int profit();
		/// <summary>
		/// Route constructor.
		/// </summary>
		/// <param name="cities">city vector</param>
		Route(vector<City> cities);
		/// <summary>
		/// Route constructor for file.
		/// </summary>
		/// <param name="route_file">file with route</param>
		/// <param name="cities">cities vector</param>
		Route(string route_file, vector<City> cities);
		bool operator==(Route& c);
	};
}

