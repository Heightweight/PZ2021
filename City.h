#pragma once
#include <string>
namespace Orienteering
{
	class City
	{
	public:
		double x;
		double y;
		int prize;
		std::string c_name; 
		City(double x=0, double y=0, int prize=-1, std::string name = "");
		bool operator==(City c);

	};
}