#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <sstream> 
using namespace std;




enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

QueryType string_to_querytype(const string& action);

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream &operator>>(istream& is, Query& q);
ostream &operator<<(ostream& os, QueryType qt);
