#include "airport.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>
using namespace std;

Airport::Airport() {};

Airport::Airport(string id, string name, double latitude, double longitude) : id_(id), name_(name) {
    latitude_ = latitude;
    longitude_ = longitude;
}

