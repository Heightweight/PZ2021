// PZ2021APP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "..\City.h"
#include "..\Road.h"
#include "..\Map.h"
#include "..\Route.h"
#include "..\City.cpp"
#include "..\Road.cpp"
#include "..\Map.cpp"
#include "..\Route.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <iostream> 
#include <sstream> 

using namespace std;

enum Mods
{
    ROAD,
    CITY,
    ROUTE,
    ERROR
};
string cities_file = "";
string roads_file = "";
string route_file = "";
vector<City> cities;
vector <Road> roads;
Map m(cities, roads);
int shop_time = -1;

void assignFile(string link, Mods modifier)
{
    ifstream ifile;
    ifile.open(link);
    if (ifile)
    {
        switch (modifier)
        {
        case ROAD:
            roads_file = link;
            break;
        case CITY:
            cities_file = link;
            break;
        case ROUTE:
            route_file = link;
            break;
        case ERROR:
            std::cout << "ERROR 001: UNKNOWN MODIFIER\n";
            break;
        default:
            std::cout << "ERROR 002: WRONG MODIFIER. TRY -r, -c or -rt\n";
        }
    }
    else
    {
        cout << "ERROR 005: FILE DOESN'T EXIST\n";
    }
}

Mods stringToMod(string input)
{
    if (input == "-r")
        return ROAD;
    if (input == "-c")
        return CITY;
    if (input == "-rt")
        return ROUTE;
    
    return ERROR;
}

void printRoute(Route r)
{
    for (int i = 0; i < r.cities.size(); i++)
        cout << r.cities[i].c_name + "->";
    cout << "\n";
}

void tokenize(string const& str, const char delim, vector<string>& out)
{
    // construct a stream from the string 
    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delim)) {
        out.push_back(s);
    }
}

int main()
{
    bool running = true;
    while (running) 
    {
        string in_str = "";
        vector<string> input;
        cout << '>';
        getline(std::cin, in_str);
        tokenize(in_str, ' ', input);
        if (input.size() != 0)
        {
            if (input[0] == "exit" || input[0] == "e")
            {
                running = false;
            }
            else if (input[0] == "read")
            {
                if (input.size() == 3)
                {
                    assignFile(input[2], stringToMod(input[1]));
                }
                else
                {
                    cout << "ERROR 003: LACKING ARGUMENTS\n";
                }
            }
            else if (input[0] == "map")
            {
                if (input.size() == 1)
                {
                    m = Map(cities_file, roads_file);
                    if (!m.check(1))
                    {
                        cout << "ERROR 004: INCORRECT MAP\n";
                    }
                    else
                    {
                        cout << "MAP LOADED SUCCESFULLY\n";
                    }
                }
                else
                    cout << "ERROR 006: UNKNOWN ARGUMENTS\n";
            }
            else if (input[0] == "set")
            {
                if (input.size() == 1)
                {
                    cout << "ERROR 003: LACKING ARGUMENTS\n";
                }
                else
                {
                    if (input[1] == "time")
                    {
                        if (input.size() != 3)
                        {
                            cout << "ERROR 008: WRONG AMOUNT OF ARGUMENTS\n";
                        }
                        else
                        {
                            shop_time = stoi(input[2]);
                        }
                    }
                }
            }
            else if (input[0] == "solve")
            {
                if (shop_time < 0)
                {
                    cout << "ERROR 007: TIME NOT SET OR INCORRECT\n";
                }
                else
                {
                    if (input.size() == 1)
                    {
                        printRoute(m.solve_h(shop_time));
                    }
                }
            }
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
