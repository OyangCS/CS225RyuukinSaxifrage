#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <string>
#include <cmath>

#include "airport.h"
#include "graph.h"
#include "utils.h"

using namespace std;

// Recommended to use find and replace all by using the current arguments in constructor 
// Users may have different paths to the data files
// Also suggest doing test cases one by one
// ./test (name of test including "")

TEST_CASE("Test Graph Constructor (Data Parsing and Mapping)") {

    Graph test("airportsfile", "routesfile");

    // Undirected Graph Mapping
    REQUIRE(test.UndirectedContains("2597", "2531"));
    REQUIRE(test.UndirectedContains("2531", "2597"));

    REQUIRE(test.UndirectedContains("6014", "2531") == false);

    // Directed Graph Mapping 
    REQUIRE(test.DirectedContains("340", "2910"));
    REQUIRE(test.DirectedContains("4041", "3830"));
    REQUIRE(test.DirectedContains("1926", "3550"));

    REQUIRE(test.DirectedContains("6014", "2531") == false);

    // ID-to-Airport Mapping
    Airport one = test.IDToAirport("596");
    REQUIRE(one.id_ == "596");
    REQUIRE(one.name_ == "Cork Airport");
    REQUIRE(one.latitude_ == 51.84130096435547);
    REQUIRE(one.longitude_ == -8.491109848022461);

    Airport two = test.IDToAirport("2745");
    REQUIRE(two.id_ == "2745");
    REQUIRE(two.name_ == "Jose Maria Córdova International Airport");
    REQUIRE(two.latitude_ == 6.16454);
    REQUIRE(two.longitude_ == -75.4231);

    Airport three = test.IDToAirport("5582");
    REQUIRE(three.id_ == "5582");
    REQUIRE(three.name_ == "Mo i Rana Airport");
    REQUIRE(three.latitude_ == 66.363899230957);
    REQUIRE(three.longitude_ == 14.301400184631);
}

TEST_CASE("BFS Shortest Path") {
    Graph test("airportfile", "routesfile");

    // Starting ID does not exist in directed graph but exists in airport data
    REQUIRE(test.BFSShortestPath("6014", "99").empty());

    // Test for direct neighbors
    vector<string> solution = { "99", "49" };

    REQUIRE(solution == test.BFSShortestPath("99", "49"));

    // Test for 3 airport paths
    solution = { "1371", "1335", "1074" };

    REQUIRE(test.BFSShortestPath("1371", "1074") == solution);

    // Test for multiple possible paths
    // { "1354", "342", "1555", "3830" } 
    // Another possible path but not shortest Path
    solution = { "1354", "146", "3830" };

    REQUIRE(test.BFSShortestPath("1354", "3830") == solution);

}

// Use small_test_graph for first input and small_test_route for second input
// Second method for calculating shortest path
TEST_CASE("Test Shortest Path") {
    /*
    this graph is a unweighted undirected graph used to test function to calculate the betweenness centrality
    A - B - D - F
         \ / \ /
          C - E
    retrieved from https://blog.csdn.net/houzhizhen/article/details/109316236
    bc : betweenness centrality
    bc of A : 0
    bc of B : 8
    bc of C : 2
    bc of D : 7
    bc of E : 1
    bc of F : 0
    */
    
    // Replace paths if necessary
    Graph test(".../CS225RyuukinSaxifrage/cs225_project/data/small_test_graph.txt", ".../CS225RyuukinSaxifrage/cs225_project/data/small_test_routes.txt");

    vector<string> path = test.shortest_path("A", "D");
    vector<string> expected = {"A", "B", "D"};
    REQUIRE(path == expected);

    path = test.shortest_path("C", "F");
    expected = {"C", "D", "F"};
    REQUIRE(path == expected);

    path = test.shortest_path("A", "F");
    expected = {"A", "B", "D", "F"};
    REQUIRE(path == expected);

}

// Use small_test_graph for first input and small_test_route for second input
TEST_CASE("Test Betweenness centrality") {
    
    // Replace paths if necessary
    Graph test(".../CS225RyuukinSaxifrage/cs225_project/data/small_test_graph.txt", ".../CS225RyuukinSaxifrage/cs225_project/data/small_test_routes.txt");
    
    /*
    this graph is a unweighted undirected graph used to test function to calculate the betweenness centrality
    A - B - D - F
         \ / \ /
          C - E
    retrieved from https://blog.csdn.net/houzhizhen/article/details/109316236
    bc : betweenness centrality
    bc of A : 0
    bc of B : 8
    bc of C : 2
    bc of D : 7
    bc of E : 1
    bc of F : 0
    */
   test.calculateBC();
   double bc_A = test.getcentrality("A");
   double bc_B = test.getcentrality("B");
   double bc_C = test.getcentrality("C");
   double bc_D = test.getcentrality("D");
   double bc_E = test.getcentrality("E");
   double bc_F = test.getcentrality("F");
   REQUIRE(bc_A == 0);
   REQUIRE(bc_B == 8);
   REQUIRE(bc_C == 2);
   REQUIRE(bc_D == 7);
   REQUIRE(bc_E == 1);
   REQUIRE(bc_F == 0);
}
