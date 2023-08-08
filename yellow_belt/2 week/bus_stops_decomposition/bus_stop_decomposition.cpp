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