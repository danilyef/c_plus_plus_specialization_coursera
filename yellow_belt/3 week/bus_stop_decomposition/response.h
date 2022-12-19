#pragma once
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <sstream> 
#include <exception>
#include <typeinfo>
using namespace std;



struct BusesForStopResponse {
    string stop;
    vector<string> buses;
};
ostream& operator << (ostream& os, const BusesForStopResponse& r);


struct StopsForBusResponse {
    string bus;
    map<string, vector<string>> bus_stop;
};
ostream& operator << (ostream& os, const StopsForBusResponse& r);


struct AllBusesResponse {
    map <string,vector<string>> buses_stops;
};
ostream& operator << (ostream& os, const AllBusesResponse& r) {
}
