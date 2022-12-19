#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <sstream> 
#include <exception>
#include "querry.h"
using namespace std;



QueryType string_to_querytype(const string& action){
    map<string,int> query_type = {
        {"NEW_BUS",0},
        {"BUSES_FOR_STOP",1},
        {"STOPS_FOR_BUS",2},
        {"ALL_BUSES",3}    
    };

    if(query_type.count(action) > 0){
        int mapping = query_type.at(action);
        return static_cast<QueryType>(mapping);
    } else{
        throw runtime_error("Wrong command: " + action);
    }
};


Query::Query(){};

Query::Query(QueryType new_type,string new_bus,string new_stop,vector<string> new_stops){
        type = new_type;
        bus = new_bus;
        stop = new_stop;
        stops = new_stops;
};




ostream& Query::operator<<(ostream& os, QueryType qt){
    const vector<string> query_names = {"NEW_BUS","BUSES_FOR_STOP","STOPS_FOR_BUS","All_BUSES"};
    os << query_names[static_cast<int>(qt)];
    return os;
}



istream& Query::operator>>(istream& is, Query& q) {
    string input;
    getline(is, input);
    stringstream stream(input);

    string query_string;
    QueryType query;

    string bus,stop,stop_name;
    int stop_count;
    vector<string> stops;

   
    stream >> query_string;
    query = string_to_querytype(query_string);

    if(query == QueryType::AllBuses){

    } else if(query == QueryType::BusesForStop){
        stream  >> stop;
    } else if(query == QueryType::NewBus){
        stream >> bus >> stop_count;
        for(int i = 0; i < stop_count; ++i){
            stream >> stop_name;
            stops.push_back(stop_name);
        }
    } else if(query == QueryType::StopsForBus){
        stream >> bus;
    } 

  

    q = Query(query,bus,stop,stops);

    return is;
}