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
#include <limits>

using namespace std;

// Inputs in the filenames for airports and routes data
Graph::Graph(const string & airports, const string & routes) {

    // Create map of id to airport
    IDToAirportMap(airports);

    // Build a map to keep track of the routes' directions
    // We only consider a route if there exists another route that goes the other way 
    map<pair<string, string>, bool> reverse_map;

    // Data Parsing 
    string file_str = file_to_string(routes);
    vector<string> data;
    SplitString(file_str, '\n', data);
    vector<string> route_temp;
    for (size_t i = 0; i < data.size(); i++) {
        SplitString(data[i], ',', route_temp);
        if (id_map_.find(route_temp[3]) != id_map_.end() && id_map_.find(route_temp[5]) != id_map_.end()) {
            double distance = calculateDistance(id_map_[route_temp[3]], id_map_[route_temp[5]]);
            if (reverse_map[make_pair(route_temp[5], route_temp[3])] == true) {
                graph_[route_temp[3]].push_back(Route(id_map_[route_temp[3]], id_map_[route_temp[5]], distance));
                graph_[route_temp[5]].push_back(Route(id_map_[route_temp[5]], id_map_[route_temp[3]], distance));
            } else {
                reverse_map[make_pair(route_temp[3], route_temp[5])] = true;
            }
            directed_[route_temp[3]].push_back(Route(id_map_[route_temp[3]], id_map_[route_temp[5]], distance));
        }
        route_temp.clear();
    }

    // For Floyd-Warshall Algorithm
    matrix_ = vector<vector<double>> (directed_.size(), vector<double> (directed_.size()));
    for (auto& it : directed_) {   
        matrix_map.push_back(it.first);
    }
}

// Info?

void Graph::IDToAirportMap(const string & airports) {
    
    // Data parsing for airports and filling out id-to-airport mapping
    string file_str = file_to_string(airports);
    vector<string> data;
    SplitString(file_str, '\n', data);
    vector<string> temp;
    for (size_t i = 0; i < data.size(); i++) {
        SplitString(data[i], ',', temp);
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
// Only for undirected graph
// Arguments are the ids of the airports
// Output of -1 indicates that there is no path or src_id/des_id does not exist

int Graph::BFSTraversal(string src_id, string des_id) {
    
    // Check if src_id and des_id both exists in the graph
    if (graph_.find(src_id) == graph_.end() || graph_.find(des_id) == graph_.end()) {
        return -1;
    }

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

void Graph::FloydWarshall() {
    // Initialize Distance Matrix
    for (size_t i = 0; i < matrix_.size(); i++) {
        for (size_t j = 0; j < matrix_.size(); j++) {
            if (i == j) {
                matrix_[i][j] = 0;
            } else {
                for (size_t k = 0; k < directed_[matrix_map[i]].size(); k++) {
                    if (directed_[matrix_map[i]][k].des_id_ == matrix_map[j]) {
                        matrix_[i][j] = directed_[matrix_map[i]][k].distance_;
                        break;
                    } else if (k + 1 == directed_[matrix_map[i]].size()) {
                        matrix_[i][j] = numeric_limits<double>::infinity();
                    }
                }
            }
        }
    }

    // Gets the final matrix after computing n (number of nodes in graph) times
    for (size_t k = 0; k < directed_.size(); k++) {
        for (size_t i = 0; i < directed_.size(); i++) {
            for (size_t j = 0; j < directed_.size(); j++) {
                matrix_[i][j] = min(matrix_[i][j], matrix_[i][k] + matrix_[k][j]);
            }
        }
    }
}