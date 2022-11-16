#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <cmath>

#include "airports.h"
#include "graph.h"
using namespace std;
int main()
{
    /*
    std::string s = "C,C++,,Java";
 
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(s);
    while (getline(ss, token, ',')){
        tokens.push_back(token);
    }
 
    for (auto &s: tokens) {
        std::cout << s << std::endl;
    }
    double p = 57.29577951;
    std::cout << p << std::endl;
    */

    /*
    Airport a;
    Airport b;
    a.latitude_ = 53.32055555555556;
    a.longitude_ = -1.7297222222222221;
    b.latitude_ = 53.31861111111111;
    b.longitude_ = -1.6997222222222223;
    double dis = calculateDistance(a,b);
    std::cout << dis << std::endl;
    */
    Airports a("/workspaces/cs225/CS225RyuukinSaxifrage/cs225_project/data/airports.dat.txt");
    /*
    vector<Airport> tmp = a.findAirportsbycity("\"Beijing\"");
    for (auto each : tmp) {
        cout<< each.name_ << endl;
    }
    */
    Graph airMap(a,"/workspaces/cs225/CS225RyuukinSaxifrage/cs225_project/data/routes.dat.txt");
    vector<Airport> v = airMap.listAdjacent(a.findAirportbyid("231"));
    for (auto each : v) {
        cout<< each.name_ << endl;
    }
    return 0;
}