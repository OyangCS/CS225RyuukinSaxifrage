#pragma once
/* 
This is the Graph class of our project!
Both directed and undirected graphs are in the class.
Airports are vertices and routes are edges; distance of routes is the weight.
*/

#include "airport.h"
#include "utils.h"

#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

// Functions as the edges of the graph
// src for source/start and des for destination
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
    // Constructor takes in paths to airport and routes CSV files
    Graph(const string & airports, const string & routes);

    // Helper function for constructor to do id-to-airport mapping
    void IDToAirportMap(const string & airports);

    // Calculate distance using Haversine formula 
    // Uses latitude and longitude 
    double calculateDistance(Airport src, Airport des);

    // Gets the associated airport based on input ID
    Airport IDToAirport(string id);

    // Testing Functions
    bool UndirectedContains(string id, string target);
    bool DirectedContains(string id, string target);
    void PrintShortestPath(string src_id, string des_id);
    
    // Calculates shortest path from src to des; inputs are IDs
    // Outputs a vector of ids that shows the order of path to take 
    vector<string> BFSShortestPath(string src_id, string des_id);

    // Floyd-Warshall
    // Utilizes whole directed graph 
    void FloydWarshall();

    // Betweenness Centrality
    void Centrality();

    // Simple method to calculate betweenness centrality
    unordered_map<string, unordered_map<string, vector<string>>> all_shortest_paths();
    double betweenness_centrality( string id);

    //find shortest path from an airport to another (different method than BFS)
    vector<string> shortest_path(string src_id, string des_id);

    //using Brandes Algorithm to calculte betweenness centrality in O(VE)
    void calculateBC();
    double getcentrality(string id);

    map<string, double> getCentrality();
    void print();
    
    private:
    // Graphs
    map<string, vector<Route>> undirected_;
    map<string, vector<Route>> directed_;

    // Utility Maps
    map<string, double> bc_; //this map stores the betweenness centrality of each airports in the graph, where key is the id of the airport

    // ID-to-Airport 
    map<string, Airport> id_map_;

    // nodes set
    vector<string> nodes;


    // Distance Between Two Airports (keys are the concatenation of two IDs)
    map<string, double> distances_;

    vector<vector<double>> matrix_;
    vector<string> matrix_map;

    unordered_map<string, double> centrality_;
};
