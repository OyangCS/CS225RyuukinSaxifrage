#pragma once
/* 
This is the Graph class of our project!
This graph is undirected but weighted.
*/

#include "airport.h"
#include "utils.h"

#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

// Functions as the edges of the graph
// src for source and des for destination
struct Route {
    Route(Airport src, Airport des, double distance) : src_(src), des_(des) {
        src_id_ = src_.id_;
        des_id_ = des_.id_;
        distance_ = distance;
    };
    Airport src_;
    Airport des_;
    string src_id_;
    string des_id_;
    double distance_;
};

class Graph {
    public:
    Graph(const string & airports, const string & routes);

    // Helper function for constructor to do id-to-airport mapping
    void IDToAirportMap(const string & airports);

    // Calculate distance using Haversine formula 
    // Uses latitude and longitude 
    double calculateDistance(Airport src, Airport des);

    // Get the associated airport with the input id
    Airport IDToAirport(string id);

    // BFS 
    // Returns number of steps needed for traversal 
    // Ex: An output of 1 means that the des is a neighbor of the src
    // An output of -1 means there is no path from src to des
    int BFSTraversal(string src_id, string des_id);


    // Floyd-Warshall Algorithm
    void FloydWarshall();


    private:
    unordered_map<string, Airport> id_map_;
    unordered_map<string, vector<Route>> graph_;
    unordered_map<string, vector<Route>> directed_;

    vector<vector<double>> matrix_;
    vector<string> matrix_map;
};