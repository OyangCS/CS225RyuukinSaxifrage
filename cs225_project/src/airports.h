#pragma once
/*
this class is used to store the data of all airports
we implement the functions for calculate the distance between two airports and two cities
also search by name and search by city
*/
#include <iostream>
#include <vector>
using namespace std;
    struct  Airport
    {
        double longitude_;
        double latitude_;
        string name_;
        string city_;
        string id_;
        string country_;
        bool operator<(const Airport& other) const {
            return id_ < other.id_;
        }
        bool operator==(const Airport& other) const {
            return id_ == other.id_;
        }
    };
class Airports {
    public :
    Airports() = default;
    Airports(string filename);
    //solve the distance between two airports by longitude and latitude using haversine formula
    // search 
    Airport findAirportbyid(string id);
    vector<Airport> findAirportsbycity(string city);
    private :
    vector<Airport> airport_map_;
    
    //unsigned num_;
};
//helper functions
vector<string> stringToVector(string);
double calculateDistance(Airport src, Airport des);