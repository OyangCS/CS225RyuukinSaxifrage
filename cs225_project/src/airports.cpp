#include "airports.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>
using namespace std;

Airports::Airports(string filename) {
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        while(getline(file, line)) {
            vector<string> temp = stringToVector(line);
            Airport tmp_airport;
            tmp_airport.id_ = temp[0];
            tmp_airport.name_ = temp[1];
            tmp_airport.city_ = temp[2];
            tmp_airport.country_ = temp[3];
            try {
                tmp_airport.latitude_ = stod(temp[6]);
                tmp_airport.longitude_ = stod(temp[7]);
            }
            catch (...) {
                tmp_airport.latitude_ = stod(temp[7]);
                tmp_airport.longitude_ = stod(temp[8]);
            }
            airport_map_.push_back(tmp_airport);
        }
    }
}
vector<Airport> Airports::findAirportsbycity(string city) {
    vector<Airport> output;
    for (auto airport: airport_map_) {
        if (airport.city_ == city) output.push_back(airport);
    }
    return output;
}
Airport Airports::findAirportbyid(string id) {
    for (auto airport: airport_map_) {
        if (airport.id_ == id) {
            return airport;
        }
    }
    Airport tmp;
    tmp.id_ = "empty";
    return tmp;
}
//using haversien formula to calculate the distance between two methods, unit is kilometer
double calculateDistance(Airport src, Airport des) {
    // convert longitude and latidude to radians
    double lat1 = src.latitude_ / 57.2958;
    double lon1 = src.longitude_ / 57.2958;
    double lat2 = des.latitude_ / 57.2958;
    double lon2 = des.longitude_ / 57.2958;
    
    // haversine formula
    double la_diff = lat2 - lat1;
    double lon_diff = lon2 - lon1;
    double temp = pow(sin(la_diff/2),2) + cos(lat1) * cos(lat2) * pow(sin(lon_diff/2),2);
    double R = 6371; // radius of the Earth in km
    temp = 2 * asin(sqrt(temp));
    double distance = R * temp;
    return distance;
}
vector<string> stringToVector(string input) {
    vector<string> output;
    string word;
    stringstream ss(input);
    while (getline(ss, word, ',')) {
        output.push_back(word);
    }
    return output;
}