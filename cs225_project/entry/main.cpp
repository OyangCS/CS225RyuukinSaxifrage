#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "airport.h"
#include "graph.h"
#include "utils.h"

using namespace std;

int main() {

    // Graph Constructor
    // First argument is path to an airports data file, and second argument is path to a routes data file
    // airports.dat.txt is the entire airport file and routes.dat.txt is the entire routes file
    // Data files are found within the data folder
    // Results in output files undirected_.txt and directed_.txt in build 
    Graph test("", "");
    
    // BFS Shortest Path
    // First argument is source airport ID and second argument is destination airport ID
    // Reference the directed graph output file from constructor for IDs 
    // Examples in test file
    // Use PrintShortestPath to create an output file in build (automatically calls BFSShortestPath)

    /*

    vector<string> bfs = test.BFSShortestPath("", "");
    // test.PrintShortestPath("", "");

    // Printing BFSShortestPath
    for (size_t i = 0; i < bfs.size(); i++) {
        cout << bfs[i] + " " + test.IDToAirport(bfs[i]).name_ + " ";
    }
    cout << endl;

    */    

   // Floyd-Warshall
   // Insufficient testing, but finishes compiling for only subsets

   // test.FloyldWarshall();

    // Betweenness Centrality
    // Recommended to not test on entire data files and use the small/subset files
    // Prints the five airports with greatest centrality
    
    /*
    test.calculateBC();
    map<string, double> centrality = test.getCentrality();
    vector<pair<string, double>> list = sortmap(centrality);
    for (unsigned i = 0; i < 5; ++i) {
        cout << test.IDToAirport(list[i].first).name_<< " with centrality: " << list[i].second <<endl;
    }
    */
   
    return 0;
}