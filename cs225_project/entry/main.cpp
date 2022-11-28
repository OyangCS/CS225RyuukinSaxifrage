#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "airport.h"
#include "graph.h"
#include "utils.h"

using namespace std;

int main() {
    
    // First argument is path of airport data; second argument is path of routes data; both are within data folder
    Graph test("/workspaces/CS225/release-f22/CS225RyuukinSaxifrage/cs225_project/data/airports.dat.txt", "/workspaces/CS225/release-f22/CS225RyuukinSaxifrage/cs225_project/data/routes.dat.txt");

    cout << test.BFSTraversal("5949", "3720") << endl;

    return 0;
}