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
		inline void append(City &c);
		/// <summary>
		/// Function of route time
		/// </summary>
		/// <param name="adjacency">adjacency matrix for current map</param>
		/// <returns>time of route</returns>
		inline double time(double** &adjacency);
		/// <summary>
		/// Function of saled stock 
		/// </summary>
		/// <returns>amount of saled stock</returns>
		inline int profit();
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
		double timeCurrent;
		bool operator==(Route& c);
	};
}

