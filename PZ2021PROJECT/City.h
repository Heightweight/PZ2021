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
		string name; 
		City(int x, int y, int prize, string name);

	};
}