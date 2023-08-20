
#include "bus_manager.h"
using namespace std;


void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    for (string stop : stops) {
      stops_to_buses[stop].push_back(bus);
    }
    buses_to_stops[bus] = stops;
  }

  BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    BusesForStopResponse stop_for_buses;
    
    if(stops_to_buses.count(stop) == 0){
        vector<string> v;
        stop_for_buses = {v};
    } else{
       stop_for_buses = {stops_to_buses.at(stop)};
    }
    
    return stop_for_buses;
  }

  StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
    StopsForBusResponse  bus_to_stops;

    if(buses_to_stops.count(bus) == 0){
        vector<string> v;
        bus_to_stops = {bus,v,stops_to_buses};
    } else{
       bus_to_stops = {bus,buses_to_stops.at(bus),stops_to_buses};
    }
    
    return bus_to_stops;

  }

  AllBusesResponse BusManager::GetAllBuses() const {
    AllBusesResponse all_buses = {buses_to_stops};
    return all_buses;
  }
