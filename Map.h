#pragma once
#include "City.h"
#include "Road.h"
#include "Route.h"
#include <vector>
#include <string>
#include <map>

using namespace std;
using namespace Orienteering;

namespace Orienteering
{
	/// <summary>
	/// Short describtion of Map class.
	/// 
	/// Class contains map with cities and roads from City class and Road class.
	/// </summary>
	class Map {
	public:
		/// <summary>
		/// Vector which contains all cities on the map.
		/// </summary>
		vector<City> cities;
		/// <summary>
		/// Vector which contains all roads on the map.
		/// </summary>
		vector<Road> roads;
		/// <summary>
		/// Tabel which contains time of traveling between two cities. If time=0 then road don't exist.
		/// </summary>
		double** adjacency;
		/// <summary>
		/// Function check conditions:
		/// - amount of stock for city is nonnegative
		/// - city coordinations are in range [-1000,1000]
		/// </summary>
		/// <returns>true if conditions are fufilled or false if not</returns>
		bool check_cities();
		//void draw();

		/// <summary>
		/// Heuristic solution of the problem.
		/// </summary>
		/// <param name="time">maximum work time of salesman</param>
		/// <returns>problem solution</returns>
		Route solve_h(double &time); //heuristic solution
		/// <summary>
		/// Explicit solution of the problem.
		/// </summary>
		/// <param name="time">maximum work time of salesman</param>
		/// <returns>problem solution</returns>
		Route solve_e(double time); //explicit solution
		/// <summary>
		/// Function check conditions:
		/// - road travel time is positive
		/// - roads are not crossed
		/// - between two cities exist maximum one road
		/// - don't exist road between one city
		/// </summary>
		/// <returns>true if conditions are fufilled or false if not</returns>
		bool check_roads();
		/// <summary>
		/// Function check correctness of map
		/// </summary>
		/// <param name="time"></param>
		/// <returns>true if conditions are fufilled or false if not</returns>
		bool check(double time);
		//void show_solution(Route solution);

		/// <summary>
		/// Map constructor for files.
		/// </summary>
		/// <param name="city_file">file with cities parameters</param>
		/// <param name="road_file">file with roads parameters</param>
		Map(string city_file, string road_file);
		/// <summary>
		/// Map constructor
		/// </summary>
		/// <param name="cities">city parameter</param>
		/// <param name="roads">road parameter</param>
		Map(vector<City> cities, vector<Road> roads);

		map<string, int> indexName;
		map<int, vector<int>> deltaFromNumber;
	};
}