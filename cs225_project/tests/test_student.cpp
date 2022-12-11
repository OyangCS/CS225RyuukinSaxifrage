#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <string>
#include <cmath>

#include "airport.h"
#include "graph.h"
#include "utils.h"

using namespace std;


TEST_CASE("Test Graph Constructor (Data Parsing and Mapping)") {

    Graph test("/workspaces/CS225/release-f22/CS225RyuukinSaxifrage/cs225_project/data/airports_huge.dat.txt", "/workspaces/CS225/release-f22/CS225RyuukinSaxifrage/cs225_project/data/routes.dat.txt");

    // Undirected Graph Mapping
    REQUIRE(test.UndirectedContains("2597", "2531"));
    REQUIRE(test.UndirectedContains("2531", "2597"));

    REQUIRE(test.UndirectedContains("6014", "2531") == false);

    // Directed Graph Mapping 
    REQUIRE(test.DirectedContains("340", "2910"));
    REQUIRE(test.DirectedContains("4041", "3830"));
    REQUIRE(test.DirectedContains("1926", "3550"));

    REQUIRE(test.UndirectedContains("6014", "2531") == false);

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

