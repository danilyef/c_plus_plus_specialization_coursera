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

#include <iostream>

#include "bus_manager.h"
#include "query.h"
#include "responses.h"


using namespace std;





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