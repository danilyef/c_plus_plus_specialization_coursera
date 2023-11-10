/*

Problem statement "Bus Stops - 1"
Implement a system for storing bus routes. You need to process the following queries:

NEW_BUS bus stop_count stop1 stop2 ... — add a bus route with the name bus and stop_count stops with names stop1, stop2, ...

BUSES_FOR_STOP stop — output the names of all bus routes passing through the stop.

STOPS_FOR_BUS bus — output the names of all stops on route bus along with a list of buses that can be transferred to at each stop.

ALL_BUSES — output a list of all routes with stops.

Input Format
The first input line contains the number of queries Q, followed by Q lines describing the queries.

It is guaranteed that all route and stop names consist only of Latin letters, digits, and underscores.

For each query NEW_BUS bus stop_count stop1 stop2 ..., it is guaranteed that the route bus does not exist, the number of stops is greater than 0, and after the number stop_count, there are exactly that many stop names, all of which are distinct within each list.

Output Format
For each query except NEW_BUS, output the corresponding response:

For the query BUSES_FOR_STOP stop, output a space-separated list of buses passing through this stop, in the order they were created by the NEW_BUS commands. If the stop stop does not exist, output No stop.

For the query STOPS_FOR_BUS bus, output the descriptions of the stops on route bus in separate lines, in the order they were given in the corresponding NEW_BUS command. The description of each stop stop should have the form Stop stop: bus1 bus2 ..., where bus1 bus2 ... is the list of buses passing through stop stop, in the order they were created by the NEW_BUS commands, except for the original route bus. If no bus passes through stop stop except for bus bus, output no interchange instead of the list of buses for it. If the route bus does not exist, output No bus.

For the query ALL_BUSES, output the descriptions of all buses in alphabetical order. The description of each route bus should have the form Bus bus: stop1 stop2 ..., where stop1 stop2 ... is the list of stops for bus route bus in the order they were given in the corresponding NEW_BUS command. If no buses are present, output No buses.



*/


#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};


istream& operator >> (istream& is, Query& q) {
  
  //type
  string type;
  is >> type;

  if(type == "NEW_BUS"){
    q.type = QueryType::NewBus;
    is >> q.bus;

    size_t stop_count = 0;
    is >> stop_count;

    q.stops.resize(stop_count);

    for(auto& elem: q.stops){
      is >> elem;
    }

  } else if (type == "BUSES_FOR_STOP"){
    //stop
    q.type = QueryType::BusesForStop;
    is >> q.stop;

  } else if (type == "STOPS_FOR_BUS"){
    //bus
    q.type = QueryType::StopsForBus;
    is >> q.bus;
    
  } else if (type == "ALL_BUSES"){
    q.type = QueryType::AllBuses;
  }
  
  return is;
}

struct BusesForStopResponse {
  vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  if (r.buses.size() == 0) {
        os << "No stop" << endl;
      } else {
        for (const string& bus : r.buses) {
          os << bus << " ";
        }
        os << endl;
      }
  return os;
}

struct StopsForBusResponse {
  string bus;
  vector<string> stops;
  map<string, vector<string>> stops_to_buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  if (r.stops.size() == 0) {
        os << "No bus" << endl;
      } else {
        for (const string& stop : r.stops) {
          os << "Stop " << stop << ": ";
          if (r.stops_to_buses.at(stop).size() == 1) {
            os << "no interchange";
          } else {
            for (const string& other_bus : r.stops_to_buses.at(stop)) {
              if (r.bus != other_bus) {
                os << other_bus << " ";
              }
            }
          }
          os << endl;
        }
      }
  return os;
}

struct AllBusesResponse {
  map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if (r.buses_to_stops.empty()) {
        cout << "No buses" << endl;
      } else {
        for (const auto& bus_item : r.buses_to_stops) {
          cout << "Bus " << bus_item.first << ": ";
          for (const string& stop : bus_item.second) {
            cout << stop << " ";
          }
          cout << endl;
        }
      }
  return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    for (string stop : stops) {
      stops_to_buses[stop].push_back(bus);
    }
    buses_to_stops[bus] = stops;
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    BusesForStopResponse stop_for_buses;
    
    if(stops_to_buses.count(stop) == 0){
        vector<string> v;
        stop_for_buses = {v};
    } else{
       stop_for_buses = {stops_to_buses.at(stop)};
    }
    
    return stop_for_buses;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    StopsForBusResponse  bus_to_stops;

    if(buses_to_stops.count(bus) == 0){
        vector<string> v;
        bus_to_stops = {bus,v,stops_to_buses};
    } else{
       bus_to_stops = {bus,buses_to_stops.at(bus),stops_to_buses};
    }
    
    return bus_to_stops;

  }

  AllBusesResponse GetAllBuses() const {
    AllBusesResponse all_buses = {buses_to_stops};
    return all_buses;
  }


private:
  map<string, vector<string>> buses_to_stops;
  map<string, vector<string>> stops_to_buses;
};

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}