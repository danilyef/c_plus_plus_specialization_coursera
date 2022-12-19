#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <sstream> 
#include <exception>
#include <typeinfo>
#include "response.h"
using namespace std;





ostream& BusesForStopResponse::operator<<(ostream& os, const BusesForStopResponse& r) {
    if(r.buses.empty()){
        os << "No stop" << endl;
    } else{
        os << r.stop << ": ";
        for(const string& bus: r.buses){
            os << bus << " ";
    }
    os << endl; 
    }
    return os;
}


ostream& StopsForBusResponse::operator<<(ostream& os, const StopsForBusResponse& r) {
    if(r.bus_stop.empty()){
        os << "No Bus" << endl;
    } else{
        os << "The bus is: " << r.bus << endl;
        for(const auto& stop: r.bus_stop){
            os << stop.first << ": ";
            if(stop.second.size() == 0){
                os << "no interchange";
            } else{
                for(const auto& other_bus: stop.second){
                        os << other_bus << " ";  
                }
            }
            os << endl;
        }   
    }
    return os;
}



ostream& AllBusesResponse::operator<<(ostream& os, const AllBusesResponse& r) {
    if(r.buses_stops.empty()){
        os << "No Buses" << endl;;
    } else{

        for (const auto& bus_item : r.buses_stops) {
            os << "Bus " << bus_item.first << ": ";
            for (const string& stop : bus_item.second) {
                os << stop << " ";
            }
            os << endl;
        }
    }

    return os;
}


