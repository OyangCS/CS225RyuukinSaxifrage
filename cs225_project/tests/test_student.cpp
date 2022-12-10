#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <string>
#include <cmath>

#include "airport.h"
#include "graph.h"
#include "utils.h"

using namespace std;


TEST_CASE("Test ID-To-Airport Mapping", "[tag1][tag2]") {

    Graph test("/workspaces/CS225/release-f22/CS225RyuukinSaxifrage/cs225_project/data/airports.dat.txt", "/workspaces/CS225/release-f22/CS225RyuukinSaxifrage/cs225_project/data/routes.dat.txt");

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