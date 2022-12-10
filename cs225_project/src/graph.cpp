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
        for (size_t i = 0; i < it.second.size(); i++) {
            distances_[it.first + it.second[i].des_id_] = it.second[i].distance_;
        }
    
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
        id_map_[temp[0]] = Airport(temp[0], TrimQuotations(temp[1]), latitude, longitude);
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
    return id_map_[id];
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

void Graph::Centrality() {
    // Initialize centrality map
    for (auto& it : graph_) {
        centrality_[it.first] = 0;
    }

    // Calculate centrality
    for (auto& it : centrality_) {
        it.second = betweenness_centrality(it.first);
    }

   
}

//calculate the betweenness centrality of a given node using brandes algorithm

double Graph::betweenness_centrality(string airport_id) {
    unordered_map<string, unordered_map<string, vector<string>>> shortest_paths = all_shortest_paths();
    
    // Initialize a variable to store the number of 
    //shortest paths that pass through the given node

    int num_shortest_paths = 0;

    // Iterate over all pairs of nodes in the graph
    for (auto& it : graph_) {
        for (auto& it2 : graph_) {
            if (it.first != it2.first) {
                // Iterate over all shortest paths between the two nodes
                for (size_t i = 0; i < shortest_paths[it.first][it2.first].size(); i++) {
                    // Check if the given node is in the path
                    if (shortest_paths[it.first][it2.first][i] == airport_id) {
                        num_shortest_paths++;
                    }
                }
            }
        }
    }

    return static_cast<double>(num_shortest_paths) / static_cast<double>(shortest_paths.size());

}



// Returns the shortest path between src_id and des_id
// using Dijkstra's algorithm
// Returns an empty vector if there is no path or src_id/des_id does not exist

vector<string> Graph::shortest_path(string src_id, string des_id) {
    // Check if src_id and des_id both exists in the graph
    if (graph_.find(src_id) == graph_.end() || graph_.find(des_id) == graph_.end()) {
        return vector<string>();
    }

    // Check if the arguments are the same;
    if (src_id == des_id) {
        return vector<string>();
    }

    // Dijkstra's algorithm
    unordered_map<string, double> distance;
    unordered_map<string, string> previous;
    unordered_map<string, bool> visited;

    // Initialize distance and previous
    for (auto& it : graph_) {
        distance[it.first] = numeric_limits<double>::max();
        previous[it.first] = "";
    }

    // Initialize distance of src_id to 0
    distance[src_id] = 0;

    // Initialize priority queue
    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;
    pq.push(make_pair(0, src_id));

    // Dijkstra's algorithm
    while (!pq.empty()) {
        string current = pq.top().second;
        pq.pop();

        if (visited[current] == false) {
            for (size_t i = 0; i < graph_[current].size(); i++) {
                double alt = distance[current] + graph_[current][i].distance_;
                if (alt < distance[graph_[current][i].des_id_]) {
                    distance[graph_[current][i].des_id_] = alt;
                    previous[graph_[current][i].des_id_] = current;
                    pq.push(make_pair(alt, graph_[current][i].des_id_));
                }
            }
        }

        visited[current] = true;
    }

    // Reconstruct the path
    vector<string> path;
    string current = des_id;
    while (current != "") {
        path.push_back(current);
        current = previous[current];
    }

    reverse(path.begin(), path.end());

    return path;
}

unordered_map<string, unordered_map<string, vector<string>>> Graph::all_shortest_paths() {
    unordered_map<string, unordered_map<string, vector<string>>> shortest_paths;

    for (auto& it : graph_) {
        for (auto& it2 : graph_) {
            if (it.first != it2.first) {
                shortest_paths[it.first][it2.first] = shortest_path(it.first, it2.first);
            }
        }
    }

    return shortest_paths;
}

void Graph::FloydWarshall() {
    // Initialize Distance Matrix
    for (size_t i = 0; i < matrix_.size(); i++) {
        for (size_t j = 0; j < matrix_.size(); j++) {
            if (i == j) {
                matrix_[i][j] = 0;
            } else {
                try {
                    matrix_[i][j] = distances_.at(matrix_map[i] + matrix_map[j]);
                } catch (std::out_of_range) {
                    matrix_[i][j] = numeric_limits<double>::infinity();
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

