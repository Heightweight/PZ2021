#pragma once
#include <string>
namespace Orienteering
{
	class City
	{
	public:
		int x;
		int y;
		int prize;
		std::string c_name; 
		City(int x, int y, int prize, std::string name);
		City();
		bool operator==(City c);

	};
}