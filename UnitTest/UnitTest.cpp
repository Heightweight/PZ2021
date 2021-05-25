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
	TEST_CLASS(UnitTestMap)
	{
	public:
		TEST_METHOD(deltaCorrectness)
		{
			string cities = "C:\\Users\\heiwei\\Documents\\PZ2021\\plikicsv\\cities0.csv";
			string roads = "C:\\Users\\heiwei\\Documents\\PZ2021\\plikicsv\\roads0.csv";
			Map m(cities, roads);
			vector<City> c;
			Route empt = Route(c);
			Assert::IsTrue(m.adjacency[0][1] > 0 && empt.time(m.roads) + m.adjacency[0][1] < 20);
			Assert::IsTrue(delta(0, empt, &m, 20)[0] == 1);
		}

		TEST_METHOD(LookupCityByNameRoute)
		{
			City L(0, 0, 1, "London");
			City M(0, 5, 4, "Manchester");
			vector<City> cities = { M,L };
			Assert::IsTrue(M == lookupCityRByName("Manchester", cities));
		}
		TEST_METHOD(solveHeuristic)
		{
			string cities = "C:\\Users\\heiwei\\Documents\\PZ2021\\plikicsv\\cities0.csv";
			string roads = "C:\\Users\\heiwei\\Documents\\PZ2021\\plikicsv\\roads0.csv";
			Map m(cities, roads);
			vector<City> c;
			/*Route empt = Route(c);
			empt.append(m.cities[0]);
			Assert::IsTrue(next_r(&m, empt, 70.0).cities.size() == 2);
			Route new_r = (next_r(&m, empt, 70.0));
			Assert::IsTrue(next_r(&m, new_r, 70.0).cities.size() == 3);
			Route new_r2 = next_r(&m, new_r, 70.0);
			Assert::IsTrue(next_r(&m, new_r2, 70.0).cities.size() == 4);*/
			Assert::IsTrue(m.solve_h(70).time(m.roads) <= 70);
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
			vector<City> route = { M,L,B,L,N };
			vector<Road> roadsPassed = { r1,r2,r3,r4 };
			vector<City> c;
			Route empt = Route(c);
			Assert::AreEqual(8.0, Route(route).time(roadsPassed));
			Assert::AreEqual(0.0, empt.time(roadsPassed));
		}

		TEST_METHOD(readFromFile)
		{
			string cities = "C:\\Users\\heiwei\\Documents\\PZ2021\\plikicsv\\cities0.csv";
			string roads = "C:\\Users\\heiwei\\Documents\\PZ2021\\plikicsv\\roads0.csv";
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
			City B(2, 2, 18, "Birmingham");
			Road r1(L, B, -2.5);
			Road r2(B, M, 5);
			vector<City> cities = { M,L,B };
			vector<Road> roads = { r1,r2 };
			Map map(cities, roads);
			Assert::AreEqual(false, map.check(25));
		}
		TEST_METHOD(CityACityBTwoRoads)
		{
			City L(0, 0, 10, "London");
			City M(4, 5, 25, "Manchester");
			City B(2, 2, 18, "Birmingham");
			Road r1(L, M, 7);
			Road r2(M, L, 5);
			vector<City> cities{ M,L,B };
			vector<Road> roads{ r1,r2 };
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
		TEST_METHOD(CrossingRoads)  // B³¹d przecinaj¹ce siê drogi nie s¹ odrzucane
		{
			City L(0, 0, 10, "London");
			City M(5, 5, 25, "Manchester");
			City B(5, 0, 18, "Birmingham");
			City N(0, 5, 10, "Newcastle");
			Road r1(L, M, 7);
			Road r2(B, N, 5);
			vector<City> cities{ M,L,B,N };
			vector<Road> roads{ r1,r2 };
			Map map(cities, roads);
			Assert::AreEqual(false, map.check(20));
		}
		TEST_METHOD(AbsCityCoordinateMoreThan1000)
		{
			City L(0, 0, 10, "London");
			City M(4, -1075, 25, "Manchester");
			City B(2, 2, 18, "Birmingham");
			Road r1(L, B, 7);
			Road r2(B, M, 5);
			vector<City> cities = { M,L,B };
			vector<Road> roads = { r1,r2 };
			Map map(cities, roads);
			Assert::AreEqual(false, map.check(30));
		}
		TEST_METHOD(TwoCitiesInOnePlace)
		{
			City L(0, 0, 10, "London");
			City M(4, 5, 25, "Manchester");
			City B(2, 1, 18, "Birmingham");
			City S(2, 1, 5, "Sheffield");
			Road r1(L, B, 7);
			Road r2(B, M, 5);
			vector<City> cities{M, L, B, S};
			vector<Road> roads{r1, r2};
			Map map(cities, roads);
			Assert::AreEqual(false, map.check(30));
		}
		TEST_METHOD(PrizeLessThanZero)
		{
			City L(0, 0, 10, "London");
			City M(4, 5, 25, "Manchester");
			City B(2, 2, -18, "Birmingham");
			Road r1(L, B, 8);
			Road r2(B, M, 5);
			vector<City> cities = { M,L,B };
			vector<Road> roads = { r1,r2 };
			Map map(cities, roads);
			Assert::AreEqual(false, map.check(25));
		}
		TEST_METHOD(RoadTimeZero)
		{
			City L(0, 0, 10, "London");
			City M(4, 5, 25, "Manchester");
			City B(2, 2, 18, "Birmingham");
			Road r1(L, B, -2.5);
			Road r2(B, M, 5);
			vector<City> cities = { M,L,B };
			vector<Road> roads = { r1,r2 };
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
	TEST_CLASS(UnitTestTime)
	{
	public:
		TEST_METHOD(TimeLessThanZero)
		{
			City L(0, 0, 10, "London");
			City M(4, 5, 25, "Manchester");
			City B(2, 2, 18, "Birmingham");
			Road r1(L, B, 7);
			Road r2(B, M, 5);
			vector<City> cities = { M,L,B };
			vector<Road> roads = { r1,r2 };
			Map map(cities, roads);
			Assert::AreEqual(false, map.check(-2));
		}
	};
}
