#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "airport.h"
#include "graph.h"
#include "utils.h"

using namespace std;

int main() {

    Graph test("/workspaces/CS225/release-f22/CS225RyuukinSaxifrage/cs225_project/data/airports_huge.dat.txt", "/workspaces/CS225/release-f22/CS225RyuukinSaxifrage/cs225_project/data/routes.dat.txt");

    // First argument is path of airport data; second argument is path of routes data; both are within data folder
    // For Owen
    test.PrintShortestPath("994", "3351");
    // test.PrintShortestPath("3729", "3351");


    

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