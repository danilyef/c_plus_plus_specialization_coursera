#include "database.h"
#include <iostream>

namespace Stats {
size_t CalculateUniqueStops(const std::vector<std::string>& stops){
    std::unordered_set<std::string_view> unique_stops;
    unique_stops.reserve(stops.size());
    for(const auto& stop_name : stops){
        unique_stops.emplace(stop_name);
    }
    return unique_stops.size();
}


size_t CalculateTotalStops(const std::vector<std::string>& stops){
    return stops.size();
}

double CalculateTotalLength(const std::unordered_map<std::string, StopInformation>& stops, const std::vector<std::string>& bus_route){

    double total_length = 0;

    /*Cached coordinates*/
    std::vector<const Coordinates*> cached_coordinates;
    cached_coordinates.reserve(bus_route.size());

    for (const auto& stop_name : bus_route){
        cached_coordinates.push_back(&stops.at(stop_name).coordinates);
    }

    /*Calculate total length*/
    for(size_t i = 0; i < bus_route.size() - 1; ++i){
        total_length += ComputeDistance(*cached_coordinates[i], 
                                        *cached_coordinates[i + 1]);
    }
    return total_length;
}

}

/*Database Bus*/
void Database::AddBus(std::string bus_id, std::vector<std::string> stops,bool is_backandforth){
    bus_db.emplace(std::move(bus_id), BusInformation(std::move(stops),is_backandforth));
};



std::optional<std::reference_wrapper<const BusInformation>> Database::GetBusInfo(const std::string& bus_id) const {
    auto it = bus_db.find(bus_id);
    if (it != bus_db.end()) {
        return it->second;
    }
    return std::nullopt;
};



/*Database Stop*/
void Database::AddStop(std::string stop_name, Coordinates coordinates){
    stop_db.emplace(std::move(stop_name), StopInformation(coordinates));
};


std::optional<std::reference_wrapper<const StopInformation>> Database::GetStopInfo(const std::string& stop_name) const{
    auto it = stop_db.find(stop_name);
    if (it != stop_db.end()) {
        return it->second;
    }
    return std::nullopt;
};


/* Updates Stats */
void Database::UpdateBusStats(){

    for(auto& [bus_id, bus_info] : bus_db){

        const auto& stops_list = bus_info.bus_stops;

        /*Total stops*/ 
        const size_t total_stops = bus_info.is_backandforth ? Stats::CalculateTotalStops(stops_list) * 2 - 1 : Stats::CalculateTotalStops(stops_list);
        /*Unique stops*/
        const size_t unique_stops_count = Stats::CalculateUniqueStops(stops_list);

        /*Total length*/

        double total_length = Stats::CalculateTotalLength(stop_db, stops_list);
        if(bus_info.is_backandforth){
            total_length *= 2.0;
        }
        
        /* Update */

        bus_info.stops = total_stops;
        bus_info.unique_stops = unique_stops_count;
        bus_info.route_len = total_length;
        bus_info.is_backandforth = true;
        bus_info.found = true;

    }
};

void Database::UpdateStopStats(){
    for(auto& [bus_id, bus_info] : bus_db){
        for(const auto& stop_name : bus_info.bus_stops){
            auto it = stop_db.find(stop_name);
            if(it != stop_db.end()){
                it->second.buses.insert(bus_id);
            }
        }
    }
};





