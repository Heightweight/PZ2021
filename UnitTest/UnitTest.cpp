#include "pch.h"
#include "CppUnitTest.h"
#include "..\City.h"
#include "..\Road.h"
#include "..\Map.h"
#include "..\Route.h"
#include "..\City.cpp"
#include "..\Road.cpp"
#include "..\Map.cpp"
#include "..\Route.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(solveHeuristic)
		{
			//string cities = "C:\\Users\\heiwei\\Documents\\PZ2021\\plikicsv\\cities1.csv";
			//string roads = "C:\\Users\\heiwei\\Documents\\PZ2021\\plikicsv\\roads1.csv";
			string cities = "C:\\Users\\Kinga\\Desktop\\MiNI_PZ2021\\PZ2021\\plikicsv\\cities0.csv";
			string roads = "C:\\Users\\Kinga\\Desktop\\MiNI_PZ2021\\PZ2021\\plikicsv\\roads0.csv";
			Map m(cities, roads); 
			vector<City> c;
			//Route empt = Route(c);
			//empt.append(m.cities[0]);
			//Assert::IsTrue(next_r(&m, empt, 70.0).cities.size() == 2);
			//Route new_r = (next_r(&m, empt, 70.0));
			//Assert::IsTrue(next_r(&m, new_r, 70.0).cities.size() == 3);
			//Route new_r2 = next_r(&m, new_r, 70.0);
			//Assert::IsTrue(next_r(&m, new_r2, 70.0).cities.size() == 4);
			double t = 70;
			Assert::IsTrue(m.solve_h(t).time(m.adjacency) <= 70);
		}

		TEST_METHOD(readFromFile)
		{
			//string cities = "C:\\Users\\heiwei\\Documents\\PZ2021\\plikicsv\\cities0.csv";
			//string roads = "C:\\Users\\heiwei\\Documents\\PZ2021\\plikicsv\\roads0.csv";
			string cities = "C:\\Users\\Kinga\\Desktop\\MiNI_PZ2021\\PZ2021\\plikicsv\\cities0.csv";
			string roads = "C:\\Users\\Kinga\\Desktop\\MiNI_PZ2021\\PZ2021\\plikicsv\\roads0.csv";
			Map m(cities, roads);
			Assert::IsTrue(m.check(1));
			Assert::AreEqual(m.adjacency[0][1], 15.0);
			Assert::AreEqual(m.adjacency[1][0], 15.0);
			Assert::AreEqual(m.adjacency[0][0], 0.0);
			Assert::AreEqual(m.adjacency[1][1], 0.0);
			Assert::IsTrue(m.cities.size() == 2);
		

		}
		TEST_METHOD(Intersect2D)
		{
			City L(0, 0, 10, "London");
			City M(5, 5, 25, "Manchester");
			City B(5, 0, 18, "Birmingham");
			City N(0, 5, 10, "Newcastle");
			Road r1(L, M, 7);
			Road r2(B, N, 5);
			Assert::AreEqual(true, intersect(r1, r2));
		}
		TEST_METHOD(RoadTimeLessThan0)
		{
			City L(0, 0, 10, "London");
			City M(4, 5, 25, "Manchester");
			Road r(L, M, -2.5);
			vector<City> cities = { M,L };
			vector<Road> roads = { r };
			Map map(cities, roads);
			Assert::AreEqual(false, map.check(25));
		}
		TEST_METHOD(CityACityBTwoRoads)
		{
			City L(0, 0, 10, "London");
			City M(4, 5, 25, "Manchester");
			Road r1(L, M, 7);
			Road r2(M, L, 5);
			vector<City> cities = { M,L };
			vector<Road> roads = { r1,r2 };
			Map map(cities, roads);
			Assert::AreEqual(false, map.check(20));
		}
		TEST_METHOD(EmptyMap)
		{
			vector<City> cities = { };
			vector<Road> roads = { };
			Map map(cities, roads);
			Assert::AreEqual(false, map.check(20));
		}
		TEST_METHOD(CrossingRoads)
		{
			City L(0, 0, 10, "London");
			City M(5, 5, 25, "Manchester");
			City B(5, 0, 18, "Birmingham");
			City N(0, 5, 10, "Newcastle");
			Road r1(L, M, 7);
			Road r2(B, N, 5);
			vector<City> cities = { M,L,B,N };
			vector<Road> roads = { r1,r2 };
			Map map(cities, roads);
			Assert::AreEqual(false, map.check(20));
		}
		TEST_METHOD(AbsCityCoordinateMoreThan1000)
		{
			City M(4, -1075, 25, "Manchester");
			City L(0, 1000, 10, "London");
			vector<City> cities1 = { M };
			vector<City> cities2 = { L };
			vector<Road> roads = { };
			Map map1(cities1, roads);
			Map map2(cities2, roads);
			Assert::AreEqual(false, map1.check(30));
			Assert::AreEqual(true, map2.check(30));
		}
		TEST_METHOD(TwoCitiesInOnePlace)
		{
			City B(2, 1, 18, "Birmingham");
			City S(2, 1, 5, "Sheffield");
			vector<City> cities = { B, S };
			vector<Road> roads = { };
			Map map(cities, roads);
			Assert::AreEqual(false, map.check(30));
		}
		TEST_METHOD(PrizeLessThanZero)
		{
			City B(2, 2, -18, "Birmingham");
			vector<City> cities = { B };
			vector<Road> roads = {  };
			Map map(cities, roads);
			Assert::AreEqual(false, map.check(25));
		}
		TEST_METHOD(RoadTimeZero)
		{
			City L(0, 0, 10, "London");
			City M(4, 5, 25, "Manchester");
			Road r(L, M, 0);
			vector<City> cities = { M,L };
			vector<Road> roads = { r };
			Map map(cities, roads);
			Assert::AreEqual(false, map.check(25));
		}
		TEST_METHOD(RoadBeatweenSameCity)
		{
			City L(3.5, 4, 20, "Leicester");
			Road r(L, L, 5);
			vector<City> cities = { L };
			vector<Road> roads = { r };
			Map map(cities, roads);
			Assert::AreEqual(false, map.check(25));
		}
	};
	TEST_CLASS(UnitTest2)
	{
	public:
		TEST_METHOD(TimeLessThanZero)
		{
			City L(0, 0, 10, "London");
			City M(4, 5, 25, "Manchester");
			Road r(L, M, 7);
			vector<City> cities = { M,L };
			vector<Road> roads = { r };
			Map map(cities, roads);
			Assert::AreEqual(false, map.check(-2));
		}
	};
	TEST_CLASS(UnitTest3)
	{
	public:
		TEST_METHOD(RouteProfit)
		{
			City L(0, 0, 1, "London");
			City M(0, 5, 4, "Manchester");
			City B(5, 0, 3, "Birmingham");
			City N(0, -5, 2, "Newcastle");
			vector<City> route = { L,M,L,B,L,N };
			Assert::AreEqual(10, Route(route).profit());
		}
		TEST_METHOD(RouteTime)
		{
			City L(0, 0, 1, "London");
			City M(0, 5, 4, "Manchester");
			City B(5, 0, 3, "Birmingham");
			City N(0, -5, 2, "Newcastle");
			Road r1(M, L, 1);
			Road r2(L, B, 2);
			Road r3(B, L, 2);
			Road r4(L, N, 3);

			vector<Road> roadsPassed = { r1,r2,r3,r4 };
			vector<City> cities = { L, M, B, N };
			Map m = Map(cities, roadsPassed);
			vector<City> route = { m.cities[1],m.cities[0],m.cities[2],m.cities[0],m.cities[3] };
			Assert::AreEqual(8.0, Route(route).time(m.adjacency));
		}
		TEST_METHOD(LookUpCitiesMap)
		{
			City L(0, 0, 1, "London");
			City M(0, 5, 4, "Manchester");
			vector<City> cities = { M,L };
			Assert::AreEqual(1, lookupCity(L, cities));
		}
		TEST_METHOD(LookUpByNameRoute)
		{
			City L(0, 0, 1, "London");
			City M(0, 5, 4, "Manchester");
			vector<City> cities = { M,L };
			Assert::IsTrue(M == lookupCityRByName("Manchester", cities));
			Assert::IsFalse(L == lookupCityRByName("Manchester", cities));
		}
		TEST_METHOD(LookUpByNameMap)
		{
			City L(0, 0, 1, "London");
			City M(0, 5, 4, "Manchester");
			vector<City> cities = { M,L };
			Assert::IsTrue(M == lookupCityByName("Manchester", cities));
			Assert::IsFalse(L == lookupCityByName("Manchester", cities));
		}
		TEST_METHOD(RouteEqual)
		{
			City L(0, 0, 1, "London");
			City M(0, 5, 4, "Manchester");
			vector<City> cities = { M,L };
			Assert::AreEqual(true, Route(cities).operator==(Route({ M,L })));
			Assert::AreEqual(false, Route(cities).operator==(Route({ L,M })));
		}
		TEST_METHOD(CityEqual)
		{
			City M(0, 5, 4, "Manchester");
			City M2(0, 5, 4, "Manchester");
			City L(0, 5, 4, "London");
			Assert::AreEqual(true, M2.operator==(M));
			Assert::AreEqual(false, L.operator==(M));
		}
	};
}
