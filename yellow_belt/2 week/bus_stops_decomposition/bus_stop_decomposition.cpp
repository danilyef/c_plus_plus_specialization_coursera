#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <sstream> 
#include <exception>
#include <typeinfo>
using namespace std;


/*
Реализуйте систему хранения автобусных маршрутов. Вам нужно обрабатывать следующие запросы:

NEW_BUS bus stop_count stop1 stop2 ... — добавить маршрут автобуса с названием bus и stop_count остановками с названиями stop1, stop2, ...
BUSES_FOR_STOP stop — вывести названия всех маршрутов автобуса, проходящих через остановку stop.
STOPS_FOR_BUS bus — вывести названия всех остановок маршрута bus со списком автобусов, на которые можно пересесть на каждой из остановок.
ALL_BUSES — вывести список всех маршрутов с остановками.
Формат ввода
В первой строке ввода содержится количество запросов Q, затем в Q строках следуют описания запросов.

Гарантируется, что все названия маршрутов и остановок состоят лишь из латинских букв, цифр и знаков подчёркивания.

Для каждого запроса NEW_BUS bus stop_count stop1 stop2 ... гарантируется, что маршрут bus отсутствует, количество остановок больше 0, а после числа stop_count следует именно такое количество названий остановок, причём все названия в каждом списке различны.

Формат вывода
Для каждого запроса, кроме NEW_BUS, выведите соответствующий ответ на него:

На запрос BUSES_FOR_STOP stop выведите через пробел список автобусов, проезжающих через эту остановку, в том порядке, в котором они создавались командами NEW_BUS. Если остановка stop не существует, выведите No stop.
На запрос STOPS_FOR_BUS bus выведите описания остановок маршрута bus в отдельных строках в том порядке, в котором они были заданы в соответствующей команде NEW_BUS. Описание каждой остановки stop должно иметь вид Stop stop: bus1 bus2 ..., где bus1 bus2 ... — список автобусов, проезжающих через остановку stop, в порядке, в котором они создавались командами NEW_BUS, за исключением исходного маршрута bus. Если через остановку stop не проезжает ни один автобус, кроме bus, вместо списка автобусов для неё выведите no interchange. Если маршрут bus не существует, выведите No bus.
На запрос ALL_BUSES выведите описания всех автобусов в алфавитном порядке. Описание каждого маршрута bus должно иметь вид Bus bus: stop1 stop2 ..., где stop1 stop2 ... — список остановок автобуса bus в порядке, в котором они были заданы в соответствующей команде NEW_BUS. Если автобусы отсутствуют, выведите No buses.


*/


enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};


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


ostream &operator<<(ostream& os, QueryType qt){
    const vector<string> query_names = {"NEW_BUS","BUSES_FOR_STOP","STOPS_FOR_BUS","All_BUSES"};
    os << query_names[static_cast<int>(qt)];
    return os;
}


struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;

    Query(){};

    Query(QueryType new_type,string new_bus,string new_stop,vector<string> new_stops){
        type = new_type;
        bus = new_bus;
        stop = new_stop;
        stops = new_stops;
    }
};

istream& operator>>(istream& is, Query& q) {
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

struct BusesForStopResponse {
    string stop;
    vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
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

struct StopsForBusResponse {
    string bus;
    map<string, vector<string>> bus_stop;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {

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

struct AllBusesResponse {
    map <string,vector<string>> buses_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
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

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        if(buses_to_stops.count(bus) > 0){
            cout << "This bus already exists" << endl;
        } else{
            buses_to_stops[bus] = stops;
            for(const auto& stop:stops){
                stops_to_buses[stop].push_back(bus);
            }
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        vector<string> buses;
        if(stops_to_buses.count(stop) > 0){
            buses =  stops_to_buses.at(stop);
        } 
        BusesForStopResponse stop_buses = {stop, buses};
        return stop_buses;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        
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


    AllBusesResponse GetAllBuses() const {
        AllBusesResponse buses_stop = {buses_to_stops};
        return buses_stop;
    }

private:
    map<string, vector<string>> buses_to_stops;
    map<string, vector<string>> stops_to_buses;

};


int main(){
    Query q;
    BusManager bm;
    
    while(true){
        cin >> q;

        if(q.type == QueryType::AllBuses){
            AllBusesResponse all_buses = bm.GetAllBuses();
            cout << all_buses;
        } else if(q.type == QueryType::BusesForStop){
            BusesForStopResponse buses_for_stop = bm.GetBusesForStop(q.stop);
            cout << buses_for_stop;
        } else if(q.type == QueryType::NewBus){
            bm.AddBus(q.bus,q.stops);
        } else if(q.type == QueryType::StopsForBus){
            StopsForBusResponse stops_for_bus =  bm.GetStopsForBus(q.bus);
            cout << stops_for_bus;
        } 
    }
   
    return 0;
}













