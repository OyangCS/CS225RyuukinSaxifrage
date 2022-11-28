#pragma once

#include <iostream>
#include <vector>

using namespace std;

struct Airport {
    Airport();
    Airport(string id, string name, string country, double latitude, double longitude);

    string id_;
    string name_;
    string country_;
    double latitude_;
    double longitude_;

};
