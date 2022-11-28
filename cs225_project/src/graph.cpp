/* Your code here! */
#include "graph.h"
#include "airport.h"
#include "utils.h"

#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

// Inputs in the filenames for airports and routes data
Graph::Graph(const string & airports, const string & routes) {

    // Build a map to keep track of the routes' directions
    // We only consider a route if there exists another route that goes the other way 
    map<pair<string, string>, bool> reverse_map;

    // Build a temporary map of id to vector of ids
    map<string, vector<string>> graph;

    // Data Parsing 
    string file_str = file_to_string(routes);
    vector<string> data;
    SplitString(file_str, '\n', data);
    vector<string> route_temp;
    for (size_t i = 0; i < data.size(); i++) {
        SplitString(data[i], ',', route_temp);
        if (reverse_map[make_pair(route_temp[5], route_temp[3])] == true) {
            graph[route_temp[3]].push_back(route_temp[5]);
            graph[route_temp[5]].push_back(route_temp[3]);
        } else {
            reverse_map[make_pair(route_temp[3], route_temp[5])] = true;
        }
        route_temp.clear();
    }

    // Create map of id to airport
    IDToAirportMap(graph, airports);

    // Converts temporary map to vector of routes
    for (auto& it : graph) {
        for (size_t i = 0; i < it.second.size(); i++) {
            double distance = calculateDistance(id_map_[it.first], id_map_[it.second[i]]);
            graph_[it.first].push_back(Route(id_map_[it.first], id_map_[it.second[i]], distance));
        }
    }

    // Printing out data + testing
    /*
    for (auto& it : graph_) {
        cout << "Source: " + it.first + " Connected To: ";
        for (size_t i = 0; i < it.second.size(); i++) {
            cout << it.second[i].des_.id_ + " ";
            if (i + 1 == it.second.size()) {
                cout << '\n';
            }
        }
    }
    */
}

/* Constructor Helper
Inputs in the temporary map from constructor + file for airports
Checks if id-to-airport is necessary by using the temporary map
Routes is using only 3000~ airports while there are over 7000 in airports data
Cut down on unnecessary storage */

void Graph::IDToAirportMap(map<string, vector<string>> graph, const string & airports) {
    
    // Data parsing for airports and filling out id-to-airport mapping
    string file_str = file_to_string(airports);
    vector<string> data;
    SplitString(file_str, '\n', data);
    vector<string> temp;
    for (size_t i = 0; i < data.size(); i++) {
        SplitString(data[i], ',', temp);
        if (graph.find(temp[0]) != graph.end()) {
            double latitude;
            double longitude;
            try {
                latitude = stod(temp[6]);
                longitude = stod(temp[7]);
            } catch (std::invalid_argument) {
                latitude = stod(temp[7]);
                longitude = stod(temp[8]);
            }
            id_map_[temp[0]] = Airport(temp[0], temp[1], temp[3], latitude, longitude);
        }
        temp.clear();
    }
}

double Graph::calculateDistance(Airport src, Airport des) {
    // Convert longitude and latidude to radians
    double lat1 = src.latitude_ / 57.2958;
    double lon1 = src.longitude_ / 57.2958;
    double lat2 = des.latitude_ / 57.2958;
    double lon2 = des.longitude_ / 57.2958;
    
    // Haversine formula
    double la_diff = lat2 - lat1;
    double lon_diff = lon2 - lon1;
    double temp = pow(sin(la_diff/2),2) + cos(lat1) * cos(lat2) * pow(sin(lon_diff/2),2);
    double R = 6371; // radius of the Earth in km
    temp = 2 * asin(sqrt(temp));
    return R * temp;
}

Airport Graph::IDToAirport(string id) {
    if (id_map_.find(id) != id_map_.end()) {
        return id_map_[id];
    }
    return Airport();
}

// Returns number of airports/stops/steps needed to get from src to des
// Arguments are the ids of the airports

int Graph::BFSTraversal(string src_id, string des_id) {
    
    // Check if the arguments are the same;
    if (src_id == des_id) {
        return 0;
    }

    // BFS Queue Setup
    // to_increment is the last id of current range before increasing the number of steps
    queue<string> to_traverse;
    to_traverse.push(src_id);
    int steps = 0;
    string to_increment = src_id;

    unordered_map<string, bool> visited;

    // Traverse while-loop
    while(!to_traverse.empty()) {
        string current = to_traverse.front();
        to_traverse.pop();
        if (current == to_increment) {
            steps++;
            to_increment = graph_[current].back().des_id_;
        }

        // Visit neighbors in order 
        for (size_t i = 0; i < graph_[current].size(); i++) {
            if (graph_[current][i].des_id_ == des_id) {
                return steps;
            } else if (visited[graph_[current][i].des_id_] == false){
                to_traverse.push(graph_[current][i].des_id_);
            }
        }

        visited[current] = true;
    }
    return -1;
}