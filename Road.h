#pragma once
#include "City.h"
#include <string>
namespace Orienteering
{
	/// <summary>
	/// Short describtion of Road class.
	/// 
	/// Class contains road parameters which are important to create map.
	/// </summary>
	class Road
	{
	public:
		/// <summary>
		/// first city
		/// </summary>
		City start;
		/// <summary>
		/// second city
		/// </summary>
		City end;
		/// <summary>
		/// time of traveling between first and second city 
		/// </summary>
		double time;
		/// <summary>
		/// Constructor of Road class
		/// </summary>
		/// <param name="start">first city</param>
		/// <param name="end">second city</param>
		/// <param name="time">time of traveling between first and second city</param>
		Road(City start, City end, double time);
	};
}
