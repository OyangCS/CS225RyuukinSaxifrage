Docker environment and CMake used by CS225 assignments.

To run, do the following steps (same directions for CS225 environment):

Open a terminal with source directory (CS225RyuukinSaxifrage/cs225_project), then: 
mkdir build
cd build
cmake ..

To run main:
make main 
./main

To run tests:
make test
./test

NOTE: Paths to the data files (such as the ones used in main and test cases) might need to be updated based on the user. If paths do not work, most efficient way to replace paths/filenames in a file is probably find and replace all.

1.) Right click a data file under data folder, copy path. The entire dataset files are named airports and routes.
2.) CTRL + F for Windows and CTRL + Command Key + F for Mac (Opens find)
3.) CTRL + H for Windows and CTRL + Command Key + H for Mac (Opens replace)
4.) There should be replace all next to the replace input box

Organization:
build -> contains all output files 
data -> contains all CSV data files
entry -> main.cpp for running algorithms
src -> code for algorithms
tests -> test suites

Information For Used Functions (all functions are under the Graph class):

Graph(const string & airports, const string & routes) [Contains Output File]
    - Constructor for graph
    - Takes in paths/filenames for airport and routes data files

void IDToAirportMap(const string & airports)
    - Helper function within graph constructor
    - Parses airport CSV file and creates ID to airport data mapping

double calculateDistance(Airport src, Airport des) 
    - Calculates distance using Haversine Formula
    - Takes in a source/starting airport and destination airport
    - Uses latitude and longitude

Airport IDToAirport(string id)
    - Gets associated airport data to input ID

bool UndirectedContains(string id, string target)
    - Checks if undirected graph contains a route starting from id to target
    - Inputs are string ids of airports
    - Returns false if id does not exist

bool DirectedContains(string id, string target)
    - Checks if directed graph contains a route starting from id to target
    - Inputs are string ids of airports
    - Returns false if id does not exist

void PrintShortestPath(string src_id, string des_id) [Contains Output File]
    - Utilizes BFSShortestPath to get shortest path vector
    - Converts vector data to a output file within build folder
    - Inputs are source/starting airport ID and destination ID
    
vector<string> BFSShortestPath(string src_id, string des_id)
    - Inputs are source/starting airport ID and destination ID
    - Outputs a vector of strings that shows the order of shortest path in airport IDs
    - Similar to MP Mazes
    - Can take a long period of time for huge graphs

void FloydWarshall()
    - Floyd-Warshall algorithm that does not take in any inputs
    - Utilizes whole directed graph to construct a matrix of shortest distance between all pairs of airports
    - Takes extremely long time for huge graphs (did not finish running for us on the entire directed graph)

void calculateBC()
    - Brandes Algorithm to calculate the betweenness centrality of all nodes in the undirected and unweighted graph
    - Utilize BFS and recursive calculation
    - modifies variable bc_ in Graph class
    - bc_ is a map<string, double>, where key represents airport id and value represents the corresponding betweenness centrality
    - Time complexity: O(VE)
    - Space complexity : O(V+E)
    - with an unsightly progress bar

double getcentrality(string id)
    - input the airport id and output its corresponding betweenness centrality

map<string, double> getCentrality()
    - return bc_ (see above)

void print()
    - print the undirected graph
    - used for test

