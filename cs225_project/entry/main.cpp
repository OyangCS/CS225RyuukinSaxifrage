#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "airport.h"
#include "graph.h"
#include "utils.h"

using namespace std;

int main() {
    
    // First argument is path of airport data; second argument is path of routes data; both are within data folder
    // For Owen
    Graph test("/workspaces/CS225/release-f22/CS225RyuukinSaxifrage/cs225_project/data/airports_huge.dat.txt", "/workspaces/CS225/release-f22/CS225RyuukinSaxifrage/cs225_project/data/routes.dat.txt");
    // vector<string> one = test.BFSShortestPath("994", "3351");
    
    /*
    vector<string> one = test.BFSShortestPath("3729", "3351");

    cout << "Shortest Path: ";
    for (size_t i = 0; i < one.size(); i++) {
        cout << one[i] + " " + test.IDToAirport(one[i]).name_ + " ";
    }
    cout << endl;

    cout << test.IDToAirport("994").id_ + test.IDToAirport("3351").id_ << endl;
    */

    // For Yuhao + Qinghuai
    //Graph test("/workspaces/cs225/CS225RyuukinSaxifrage/cs225_project/data/airports_huge.dat.txt", "/workspaces/cs225/CS225RyuukinSaxifrage/cs225_project/data/routes.dat.txt");
    //test.FloydWarshall();
    //test shortest path
    /*
    unordered_map<string, unordered_map<string, vector<string>>> paths = test.all_shortest_paths();
    for (auto it = paths.begin(); it != paths.end(); it++) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            cout << it->first << " " << it2->first << " ";
            for (auto it3 = it2->second.begin(); it3 != it2->second.end(); it3++) {
                cout << *it3 << " ";
            }
            cout << endl;
        }
    }
    */
   // test.calculateBC();
   // cout << test.getcentrality("B") << endl;
   
    return 0;
}