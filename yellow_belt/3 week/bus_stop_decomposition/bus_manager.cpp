#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <sstream> 
#include <exception>
#include <typeinfo>
#include "bus_manager.h"
#include "response.h"
using namespace std;


void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    if(buses_to_stops.count(bus) > 0){
        cout << "This bus already exists" << endl;
    } else{
        buses_to_stops[bus] = stops;
        for(const auto& stop:stops){
            stops_to_buses[stop].push_back(bus);
        }
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    vector<string> buses;
    if(stops_to_buses.count(stop) > 0){
        buses =  stops_to_buses.at(stop);
    } 
    BusesForStopResponse stop_buses = {stop, buses};
    return stop_buses;
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
        
    vector<string> stops;
    map<string, vector<string>> stop_bus;


    if(buses_to_stops.count(bus) > 0){
        stops =  buses_to_stops.at(bus);
    }

    for(auto stop : stops){
        vector<string> buses;
        for(const auto& b:stops_to_buses.at(stop)){
            if(b != bus){
                buses.push_back(b);
            }
        }
        stop_bus[stop] = buses;
    }
    StopsForBusResponse stops_bus = {bus,stop_bus};
    return stops_bus;
}


AllBusesResponse BusManager::GetAllBuses() const {
    AllBusesResponse buses_stop = {buses_to_stops};
    return buses_stop;
}



