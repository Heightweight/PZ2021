#pragma once
#include <string>
namespace Orienteering
{
	/// <summary>
	/// Short describtion of City class.
	/// 
	/// Class contains city parameters which are important to create map.
	/// </summary>
	class City
	{
	public:
		/// <summary>
		/// coordination x of the city no the map
		/// </summary>
		double x;
		/// <summary>
		/// coordination y of the city no the map
		/// </summary>
		double y;
		/// <summary>
		/// amount of stock for the city
		/// </summary>
		int prize;
		/// <summary>
		/// city name
		/// </summary>
		std::string c_name; 

		/// <summary>
		/// Constructor of City class.
		/// </summary>
		/// <param name="x">coordinate x of the city (deafault 0)</param>
		/// <param name="y">coordinate y of the city (deafault 0)</param>
		/// <param name="prize">amount of stock for the city (deafault -1)</param>
		/// <param name="name">name of the city (deafault "")</param>
		City(double x=0, double y=0, int prize=-1, std::string name = "");

		/// <summary>
		/// Operator == for elements from City class
		/// </summary>
		/// <param name="c">city parameter</param>
		/// <returns>true if equal of false if not</returns>
		bool operator==(City c);

	};
}