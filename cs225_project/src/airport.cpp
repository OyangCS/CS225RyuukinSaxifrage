#include "airport.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>
using namespace std;

Airport::Airport() {};

Airport::Airport(string id, string name, string country, double latitude, double longitude) : id_(id), name_(name), country_(country) {
    latitude_ = latitude;
    longitude_ = longitude;
}

