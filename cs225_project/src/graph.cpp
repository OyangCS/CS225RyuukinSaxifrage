/* Your code here! */
#include "graph.h"
#include <fstream>
#include <algorithm>
//graph constructor
Graph::Graph() {
    
}
Graph::Graph(Airports airports, string filename) {
    
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        while(getline(file, line)) {
            vector<string> temp = stringToVector(line);
            string srcId = temp[3]; // id of source airport
            string desId = temp[5]; // id of destination airport
            Airport src = airports.findAirportbyid(srcId);
            Airport des = airports.findAirportbyid(desId);
            Route r1;
            r1.src_id = srcId;
            r1.des_id = desId;
            r1.des = des;
            r1.distance = calculateDistance(src, des);
            if (map_.find(src) == map_.end()) {
                vector<Route> temp_vect;
                temp_vect.push_back(r1);
                map_.insert(pair<Airport, vector<Route>>(src, temp_vect));
            } else {
                vector<Route> & tmp = map_[src];
                if (find(tmp.begin(),tmp.end(),r1) == tmp.end()) tmp.push_back(r1);
            }
            Route r2;
            r2.src_id = desId;
            r2.des_id = srcId;
            r2.des = des;
            r2.distance = calculateDistance(des, src);
            if (map_.find(des) == map_.end()) {
                vector<Route> temp_vect;
                temp_vect.push_back(r2);
                map_.insert(pair<Airport, vector<Route>>(des, temp_vect));
            } else {
                vector<Route> & tmp = map_[des];
                if (find(tmp.begin(),tmp.end(),r2) == tmp.end()) map_[des].push_back(r2);
            }
        }
    }
}
// this function returns the vector that contains all adjacent airports of the input airport
// helper function for BFS
vector<Airport> Graph::listAdjacent(Airport input) {
    vector<Route> routes = map_[input];
    vector<Airport> output;
    for (Route r : routes) {
        output.push_back(r.des);
    }
    return output;
}