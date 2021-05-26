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
    ERROR,
    TIME
};
string cities_file = "";
string roads_file = "";
string route_file = "";
string time_file = "";
vector<City> cities;
vector <Road> roads;
vector<string> currentRoute;
Map m(cities, roads);
Route solution = Route(vector<City>());

double shop_time = -1;

vector<string> routeFromFile(string& link)
{
    vector<string> route;
    ifstream ifile;
    ifile.open(link);
    string read = "";
    if (ifile)
    {
        getline(ifile, read);
        if (read == "solution")
        {
            while (getline(ifile, read))
            {
                route.push_back(read);
            }
            return route;
        }
    }
    return route;

}

void assignFile(string link, Mods modifier)
{
    ifstream ifile;
    ifile.open(link);
    string read = "";
    if (ifile)
    {
        getline(ifile, read);
        switch (modifier)
        {
        case ROAD:
            if (read == "city1,city2,travel_time")
                roads_file = link;
            else
                cout << "ERROR 009: UNKNOWN FILE FORMAT\n";
            break;
        case CITY:
            if (read == "city_name,x_coordinate,y_coordinate,commodity")
                cities_file = link;
            else
                cout << "ERROR 009: UNKNOWN FILE FORMAT\n";
            break;
        case ROUTE:
            if (read == "solution")
                route_file = link;
            else
                cout << "ERROR 009: UNKNOWN FILE FORMAT\n";
            break;
        case TIME:
            if (read == "time")
                time_file = link;
            else
                cout << "ERROR 009: UNKNOWN FILE FORMAT\n";
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

void displayMap(Map& m)
{
    if (m.cities.size() > 0)
    {
        for (int i = 0; i < m.cities.size() - 1; ++i)
        {
            cout << m.cities[i].c_name + ", ";
        }
        cout << m.cities.back().c_name + "\n";

        for (int i = 0; i < m.roads.size(); ++i)
        {
            cout << m.roads[i].start.c_name + " - " + m.roads[i].end.c_name + "\n";
        }
    }
    else
        cout << "THE MAP IS EMPTY. \n";
}

void setTimeFromFile(double& t, string& time_file)
{
    ifstream ifile;
    ifile.open(time_file);
    string read = "";
    if (ifile)
    {
        getline(ifile, read);
        if (read == "time")
        {
            getline(ifile, read);
            t = stod(read);
        }
        else
        {
            cout << "ERROR 009: UNKNOWN FILE FORMAT\n";
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
    if (input == "-t")
        return TIME;
    
    return ERROR;
}

void printRoute(Route &r, Map &m)
{
    if (r.cities.size() == 0)
    {
        cout << "ERROR 010: NOTHING TO PRINT\n";
    }
    else if (m.cities.size() == 0)
    {
        cout << "ERROR 011: THE MAP HAS NOT BEEN SET CORRECTLY\n";
    }
    else
    {
        bool flag = false;
        
        for (int i = 0; i < r.cities.size() - 1; ++i)
        {
            if (m.adjacency[r.cities[i].nubmerAssigned][r.cities[i + 1].nubmerAssigned] <= 0)
            {
                cout << "ERROR 012: THERE IS A ROAD MISSING OR THE MAP HAS NOT BEEN SET UP PROPERLY. \n";
                flag = true;
                break;
            }
        }

        for (int i = 0; i < r.cities.size(); ++i)
        {
            if (r.cities[i].prize < 0)
            {
                cout << "ERROR 012: THERE IS A CITY MISSING OR THE MAP HAS NOT BEEN SET UP PROPERLY. \n";
                flag = true;
                break;
            }
        }

        if (!flag)
        {
            for (int i = 0; i < r.cities.size() - 1; ++i)
                cout << r.cities[i].c_name + "->";
            cout << r.cities.back().c_name + '\n';
            cout << "PROFIT: " + to_string(r.profit()) + "\n";
            cout << "TIME TOTAL: " + to_string(r.time(m.adjacency)) + "\n";
            cout << "\n";
        }
    }
   
}

Route convertRoute(vector<string>& r, Map& m)
{
    Route route = Route(vector<City>());
    if (r.size() == 0)
    {
        cout << "ERROR 010: NOTHING TO PRINT\n";
    }
    else if (m.cities.size() == 0)
    {
        cout << "ERROR 011: THE MAP HAS NOT BEEN SET CORRECTLY\n";
    }
    else
    {
        for (int i = 0; i < r.size(); i++)
        {
            string name = r[i];
            City city = lookupCityByName(name, m.cities);
            route.append(city);
        }
    }
    return route;

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
    cout << "PZ2021 0.9.98\n";
    cout << "Type \"help\" to see all available commands.\n";
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
            else if (input[0] == "help")
            {
                if (input.size() != 1)
                {
                    cout << "ERROR 014: UNKNOWN HELP MODIFIER. TRY \"help\"\n";
                }
                else
                {
                    cout << "help --- displays all available commands\n";
                    cout << "read -modifier fileAddress  --- reads a file from fileAddress as an appropriate data type:\n";
                    cout << "\t -r --- reads as a roads file \n";
                    cout << "\t -rt --- reads as a route file \n";
                    cout << "\t -c --- reads as a cities file \n";
                    cout << "\t -t --- reads as a time file \n";
                    cout << "map --- attempts to read a map from assigned roads and cities files\n";
                    cout << "set time <optionalNumber> --- attempts to set time from the file. If a \n";
                    cout << "number was provided, sets the time to the number instead. \n";
                    cout << "solve --- finds an approximate solution for a current map.\n";
                    cout << "show -modifier --- shows data according to a modifier:\n";
                    cout << "\t -rt --- shows the route loaded from a file \n";
                    cout << "\t -m --- shows a current map \n";
                    cout << "preset --- loads a preset of data for you\n";
                    cout << "save fileName --- saves the current route to a fileName.csv file.\n";

                }
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
                        if (input.size() == 2)
                        {
                            setTimeFromFile(shop_time, time_file);
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
                        solution = m.solve_h(shop_time);
                        printRoute(solution, m);
                    }
                }
            }
            else if (input[0] == "show")
            {
                if (input.size() == 1)
                    displayMap(m);
                else if (input.size() == 2)
                {
                    if (input[1] == "-rt")
                    {
                        vector<string> names = routeFromFile(route_file);
                        Route route = convertRoute(names, m);
                        printRoute(route, m);
                    }
                    else if (input[1] == "-m")
                    {
                        displayMap(m);
                    }
                    else
                        cout << "ERROR 001: UNKNOWN MODIFIER\n";
                }
                else
                    cout << "ERROR 008: WRONG AMOUNT OF ARGUMENTS\n";
            }
            else if (input[0] == "preset")
            {
                assignFile("..\\plikicsv\\cities1.csv", CITY);
                assignFile("..\\plikicsv\\roads1.csv", ROAD);
                assignFile("..\\plikicsv\\time1.csv", TIME);
                assignFile("..\\plikicsv\\route1.csv", ROUTE);
            }
            else if (input[0] == "save")
            {
                if (input.size() != 2)
                {
                    cout << "ERROR 008: WRONG AMOUNT OF ARGUMENTS\n";
                }
                else if (route_file == "" && solution.cities.size() == 0)
                {
                    cout << "NOTHING TO SAVE\n";
                }
                else
                {
                    ofstream ofile;
                    ofile.open(input[1] + ".csv");
                    if (solution.cities.size() != 0)
                    {
                        ofile << "solution\n";
                        for (int i = 0; i < solution.cities.size(); ++i)
                            ofile << solution.cities[i].c_name + "\n";
                        ofile.close();
                    }
                    else
                    {
                        vector<string> names = routeFromFile(route_file);
                        Route route = convertRoute(names, m);
                        ofile << "solution\n";
                        for (int i = 0; i < solution.cities.size(); ++i)
                            ofile << solution.cities[i].c_name + "\n";
                        ofile.close();
                    }
                }

            }
            else 
            cout << "ERROR 013: UNKNOWN COMMAND\n";

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
