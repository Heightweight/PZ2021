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
		City(int x=0, int y=0, int prize=-1, std::string name = "");
		bool operator==(City c);

	};
}