#pragma once
#include <string>

using namespace std;

namespace Orienteering
{
	class City
	{
	public:
		int x;
		int y;
		int prize;
		string c_name; 
		City();
		City(int x, int y, int prize, string name);
		bool operator==(City c);
	};
}