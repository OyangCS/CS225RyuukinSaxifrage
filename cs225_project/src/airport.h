#pragma once

#include <iostream>
#include <vector>

using namespace std;

// Simple Airport struct to hold data
struct Airport {
    Airport();
    Airport(string id, string name, double latitude, double longitude);

    string id_;
    string name_;
    double latitude_;
    double longitude_;

};
