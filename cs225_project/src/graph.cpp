/* Your code here! */
#include "graph.h"
#include "airport.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

// Inputs in the paths/filenames for airports and routes data
Graph::Graph(const string & airports, const string & routes) {

    // Create map of id to airport
    IDToAirportMap(airports);

    // Build a map to keep track of the routes' directions for undirected graph
    // We only consider a route if there exists another route that goes the other way 
    map<pair<string, string>, bool> reverse_map;

    // Data Parsing
    // It first converts the entire file to one long string, then splits the string based on '\n' or lines
    // At each index of the data vector holds a string representing a line of the dataset
    // We iterate through the vector and add each line of data to the map
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
                if(find(nodes.begin(),nodes.end(),route_temp[3])==nodes.end())nodes.push_back(route_temp[3]);
                if(find(nodes.begin(),nodes.end(),route_temp[5])==nodes.end())nodes.push_back(route_temp[5]);
            } else {
                reverse_map[make_pair(route_temp[3], route_temp[5])] = true;
            }
            directed_[route_temp[3]].push_back(Route(id_map_[route_temp[3]], id_map_[route_temp[5]], distance));
        }
        route_temp.clear();
    }

    // Output file to show undirected graph
    ofstream undirect ("undirected_.txt");
    if (undirect.is_open()) {
        for (auto& it : graph_) {
            undirect << it.first + " is connected to: ";
            for (size_t i = 0; i < it.second.size(); i++) {
                undirect << it.second[i].des_id_ + " ";
            }
            undirect << endl;
        }
        undirect.close();
    }

    // Output file to show directed graph
    ofstream direct ("directed_.txt");
    if (direct.is_open()) {
        for (auto& it : directed_) {
            direct << it.first + " is connected to: ";
            for (size_t i = 0; i < it.second.size(); i++) {
                direct << it.second[i].des_id_ + " ";
            }
            direct << endl;
        }
        direct.close();
    }

    // For Floyd-Warshall Algorithm
    // matrix_ = vector<vector<double>> (directed_.size(), vector<double> (directed_.size()));
    // for (auto& it : directed_) {   
    //     matrix_map.push_back(it.first);
    //     for (size_t i = 0; i < it.second.size(); i++) {
    //         distances_[it.first + it.second[i].des_id_] = it.second[i].distance_;
    //     }
    // }
}


// Creates a map that pairs unique ids (strings) to airport data (name, country, latitude, and longitude)
// The dataset itself provides unique ids and the id of each airport is the first data entry of the line
void Graph::IDToAirportMap(const string & airports) {
    
    // Data parsing for airports and filling out id-to-airport mapping
    // Same method as the one for routes dataset
    string file_str = file_to_string(airports);
    vector<string> data;
    SplitString(file_str, '\n', data);
    vector<string> temp;
    for (size_t i = 0; i < data.size(); i++) {
        SplitString(data[i], ',', temp);
        // We split the data of each line by commas, and some lines contain an extra comma in the name entry
        // This messes up string to double conversion for some lines, so we use try-catch
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


// Calculates distance between two airports using Haversine formula
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

// Function to get airport data 
Airport Graph::IDToAirport(string id) {
    if (id_map_.find(id) != id_map_.end()) {
        return id_map_.at(id);
    }
    cout << "The requested " + id + " does not exist." << endl;
    return Airport();
}

// Checks if the neighbors of id in undirected graph contains target
bool Graph::UndirectedContains(string id, string target) {
    if (graph_.find(id) == graph_.end()) {
        return false;
    }
    for (size_t i = 0; i < graph_[id].size(); i++) {
        if (graph_[id][i].des_id_ == target) {
            return true;
        }
    }
    return false;
}

// Checks if the neighbors of id in directed graph contains target
bool Graph::DirectedContains(string id, string target) {
    if (directed_.find(id) == directed_.end()) {
        return false;
    }
    for (size_t i = 0; i < directed_[id].size(); i++) {
        if (directed_[id][i].des_id_ == target) {
            return true;
        }
    }
    return false;
}

/* 
BFS Traversal (using directed graph)
Arguments are starting airport and destination airport (in IDs)
Outputs a vector of strings/IDs representing shortest path in order
An empty vector indicates that no path exists
*/
vector<string> Graph::BFSShortestPath(string src_id, string des_id) {

    // Check for nonexisting ids and same arguments
    if(directed_.find(src_id) == directed_.end() || directed_.find(des_id) == directed_.end()) {
        return vector<string>();
    } else if (src_id == des_id) {
        return vector<string> { src_id, des_id };
    }

    // Setting up BFS queue, visited maps, and vector of all possible maps
    // pair contains the path vector and double for total distance traveled
    queue<pair<vector<string>, double>> to_traverse;
    unordered_map<string, bool> visited;
    to_traverse.push(make_pair(vector<string> { src_id }, 0));
    vector<pair<vector<string>, double>> paths;

    while(!to_traverse.empty()) {

        // Get front vector of queue and push neighbors of last value of vector
        // Change visited of current to true
        pair<vector<string>, double> current = to_traverse.front();
        to_traverse.pop();
        vector<Route> current_vec = directed_[current.first.back()];
        visited[current.first.back()] = true;

        // Construct paths based on neighbors of current in order (BFS)
        // To avoid creating vectors, we use push_back and pop_back with current vector
        // Check if visited is false before proceeding
        // If neighbor == des_id, we push the path vector to paths rather than to the queue
        for (size_t i = 0; i < current_vec.size(); i++) {
            if (visited[current_vec[i].des_id_] == false) {
                current.first.push_back(current_vec[i].des_id_);
                current.second += current_vec[i].distance_;
                if (current_vec[i].des_id_ == des_id) {
                    paths.push_back(current);
                } else {
                    to_traverse.push(current);
                }
                current.first.pop_back();
                current.second -= current_vec[i].distance_;
            }
        }
    }

    // Find mininum distance traveled among all possible paths
    if (!paths.empty()) {
        int shortest_index = 0;
        double min = paths[0].second;
        for (size_t i = 1; i < paths.size(); i++) {
            if (paths[i].second < min) {
                shortest_index = i;
                min = paths[i].second;
            }
        }
        return paths[shortest_index].first;
    }

    return vector<string>();
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



/* 
Returns the shortest path between src_id and des_id
using Dijkstra's algorithm
Returns an empty vector if there is no path or src_id/des_id does not exist
*/

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
    // The matrix_ is a n x n 2D vector, where n is the number of nodes
    // matrix_map is a 1D vector to map each node to an int (the index of the vector)
    // Try-catch block to see if there is a route directly from the source
    // Infinite distance if there does not exist a direct route
    for (size_t i = 0; i < matrix_.size(); i++) {
        for (size_t j = 0; j < matrix_.size(); j++) {
            // When i == j, the distance is 0 because the source and destination are the same
            // Forms a diagonal of 0s in the 2D matrix
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
    // The triple for-loop of Floyd-Warshall
    // O(n^3)
    for (size_t k = 0; k < matrix_map.size(); k++) {
        for (size_t i = 0; i < matrix_map.size(); i++) {
            for (size_t j = 0; j < matrix_map.size(); j++) {
                // Min for shortest distance
                matrix_[i][j] = min(matrix_[i][j], matrix_[i][k] + matrix_[k][j]);
            }
        }
    }
}


//implement betweenness centrality using Brandes Algorithm
void Graph::calculateBC() {
    map<string, double> dependency;
    map<string, double> dist;
    map<string, vector<string>> pred;
    map<string, double> num_path;
    cout<< "start!!" <<endl;
    cout<< "number: " << nodes.size()<< endl;
    for (auto i = graph_.begin(); i != graph_.end(); ++i) {
        pair<string, double> p(i->first, 0);
        pair<string, double> p1(i->first, 0);
        pair<string, double> p2(i->first, -1);
        pair<string, vector<string>> p3(i->first, vector<string>());
        pair<string, double> p4(i->first, 0);
        bc_.insert(p);
        dependency.insert(p1);
        dist.insert(p2);
        pred.insert(p3);
        num_path.insert(p4);
    }
    int count = 1;
    for(string s : nodes) {
        cout<< count << "/"<< nodes.size() << endl;
        //cout<< "from" << s << endl;
        count++;
        stack<string> S;
        map<string, vector<string>> P = pred;
        map<string, double> num_path_ = num_path;
        num_path_[s] = 1;
        map<string, double> d = dist;
        d[s] = 0;
        queue<string> Q;
        Q.push(s);
        while(!Q.empty()) {
            string v = Q.front();
            Q.pop();
            S.push(v);
            for (auto r = graph_[v].begin(); r !=graph_[v].end(); ++r) {
                string w = r->des_id_;
                if (d[w] < 0) {
                    Q.push(w);
                    d[w] = d[v] + 1;
                }
                if (d[w] == d[v] + 1) {
                    num_path_[w] = num_path_[w] + num_path_[v];
                    P[w].push_back(v);
                }
            }
        }
        map<string, double> dependency_ = dependency;
        while(!S.empty()) {
            string w = S.top();
            S.pop();
            for (string v : P[w]) {
                dependency_[v] = dependency_[v] + (num_path_[v]/num_path_[w]) * (1 + dependency_[w]);
            }
                if (w != s) bc_[w] = bc_[w] + dependency_[w];
        }
    }
}

double Graph::getcentrality(string id) {
    return bc_[id];
}

void Graph::print() {
    for (auto i = graph_.begin(); i != graph_.end(); ++i) {
        string src = i->first;
        for (auto r = graph_[src].begin(); r !=graph_[src].end(); ++r) {
            string w = r->des_id_;
            cout << src << "->" << w<<endl;
        }
    }
}

void Graph::PrintShortestPath(string src_id, string des_id) {
    vector<string> vec = BFSShortestPath(src_id, des_id);
    ofstream myfile (src_id + "to" + des_id + ".txt");
    if (myfile.is_open()) {
        myfile << "Shortest Path from " + src_id + " to " + des_id + ": " << endl; 
        if (!vec.empty()) {
            for (size_t i = 0; i < vec.size(); i++) {
                myfile << vec[i] + " " + id_map_[vec[i]].name_ << endl;
            }
        } else {
            myfile << "No Path Exists For These Two Airports" << endl;
        }
        myfile.close();
    }
}
