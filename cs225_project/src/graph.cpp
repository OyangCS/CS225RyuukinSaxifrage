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

unordered_map<string, unordered_map<string, vector<string>>> Graph::all_shortest_paths() {

    // Initialize a map to store the shortest paths between each pair of nodes

    std::unordered_map<string, std::unordered_map<string, vector<string>>> shortest_paths;

    //Iterate over all pairs of nodes in the graph
    for (auto& it : graph_) {
        // Create a map to store the distances from the starting node to each other node in the graph
        unordered_map<string, double> distances;

        // Create a priority queue to store the nodes to visit
        // ordered by their distance from the starting node
        priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> to_visit;

        // Initialize the distances to all nodes as infinity, except for the starting node
        for (auto& it2 : graph_) {
            if (it.first == it2.first) {
                distances[it2.first] = 0;
            } else {
                distances[it2.first] = numeric_limits<double>::infinity();
            }
        }

        // Insert the starting node into the priority queue
        to_visit.push(make_pair(0, it.first));

        // while the priority queue is not empty
        while (!to_visit.empty()) {
            // Get the node with the smallest distance from the starting node
            string current = to_visit.top().second;
            to_visit.pop();

            // Iterate over all neighbors of the current node
            for (size_t i = 0; i < graph_[current].size(); i++) {
                // Get the distance from the starting node to the neighbor
                double distance = distances[current] + graph_[current][i].distance_;

                // If the distance is less than the current distance to the neighbor
                if (distance < distances[graph_[current][i].des_id_]) {
                    // Update the distance to the neighbor
                    distances[graph_[current][i].des_id_] = distance;

                    // Insert the neighbor into the priority queue
                    to_visit.push(make_pair(distance, graph_[current][i].des_id_));
                }
            }
        }

        // Iterate over all nodes in the graph
        for (auto& it2 : graph_) {
            // Create a vector to store the shortest path from the starting node to the current node
            vector<string> path;

            // Get the current node
            string current = it2.first;

            // While the current node is not the starting node
            while (current != it.first) {
                // Add the current node to the path
                path.push_back(current);

                // Iterate over all neighbors of the current node
                for (size_t i = 0; i < graph_[current].size(); i++) {
                    // If the distance from the starting node to the neighbor is equal to the distance from the starting node to the current node minus the distance from the current node to the neighbor
                    if (distances[graph_[current][i].des_id_] == distances[current] - graph_[current][i].distance_) {
                        // Set the current node to the neighbor
                        current = graph_[current][i].des_id_;
                        break;
                    }
                }
            }

            // Add the starting node to the path
            path.push_back(it.first);

            // Reverse the path
            reverse(path.begin(), path.end());

            // Add the path to the map
            shortest_paths[it.first][it2.first] = path;
        }


    }

    return shortest_paths;
}
