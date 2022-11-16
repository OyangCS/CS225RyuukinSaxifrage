#pragma once
/* 
This is the Graph class of our project!
This graph is undirected but weighted.
we assume that if there is a route from A to B, 
then there will be a route from B to A 
*/
#include "airports.h"
#include <map>
#include <vector>
using namespace std;
// function same as Edge struct
struct Route {
    string src_id;
    string des_id;
    Airport des;
    double distance;
    bool operator==(const Route& other) const {
            return (src_id == other.src_id && des.id_ == des.id_);
        }
};
class Graph {
    public :
    Graph();
    Graph(Airports airports, string filename);
    vector<Airport> listAdjacent(Airport);

    Route findShortestRoute(Airport src, Airport des);
    private :

    map<Airport, vector<Route>> map_;
};
