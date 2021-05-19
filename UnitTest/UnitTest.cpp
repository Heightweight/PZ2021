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
			vector<City> cities = { M,L,B };
			vector<Road> roads = { r1,r2 };
			Map map(cities, roads);
			Assert::AreEqual(false, map.check(13));
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
			vector<City> cities = { M,L,B };
			vector<Road> roads = { r1,r2 };
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
			vector<City> cities = { M,L,B };
			vector<Road> roads = { r1,r2 };
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
