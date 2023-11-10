
#include "query.h"

using namespace std;

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