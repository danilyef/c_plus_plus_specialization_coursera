#include "database.h"
#include <iostream>
#include <cmath>

namespace DatabaseStats {


double ComputeDistanceCoordinates(const Descriptions::Coordinates& lhs, const Descriptions::Coordinates& rhs) {
    // to radians
    double lat1_rad = lhs.latitude * DEG_TO_RAD;
    double lon1_rad = lhs.longitude * DEG_TO_RAD;
    double lat2_rad = rhs.latitude * DEG_TO_RAD;
    double lon2_rad = rhs.longitude * DEG_TO_RAD;

    // Calculate distance by formula
    double delta_lon = std::abs(lon1_rad - lon2_rad);
    double distance = std::acos(std::sin(lat1_rad) * std::sin(lat2_rad) +
                                std::cos(lat1_rad) * std::cos(lat2_rad) *
                                std::cos(delta_lon)) * 6371000;  

    return distance;
}


int CalculateUniqueStops(const std::vector<std::string>& stops){
    std::unordered_set<std::string_view> unique_stops;
    unique_stops.reserve(stops.size());
    for(const auto& stop_name : stops){
        unique_stops.emplace(stop_name);
    }
    return unique_stops.size();
}


int CalculateTotalStops(const std::vector<std::string>& stops){
    return stops.size();
}

double CalculateTotalLengthCoordinates(const std::unordered_map<std::string, Descriptions::StopInformation>& stops, const std::vector<std::string>& bus_route, bool is_roundtrip){

    double total_length = 0;

    /*Cached coordinates*/
    std::vector<const Descriptions::Coordinates*> cached_coordinates;
    cached_coordinates.reserve(bus_route.size());

    for (const auto& stop_name : bus_route){
        cached_coordinates.push_back(&stops.at(stop_name).coordinates);
    }

    /*Calculate total length*/
    for(size_t i = 0; i < bus_route.size() - 1; ++i){
        total_length += ComputeDistanceCoordinates(*cached_coordinates[i], 
                                        *cached_coordinates[i + 1]);
    }

    if(!is_roundtrip){
        total_length *= 2.0;
    }
    return total_length;
}

int CalculateTotalLengthStops(const std::unordered_map<std::string, Descriptions::StopInformation>& stops, const std::vector<std::string>& bus_route, bool is_roundtrip){
    int total_length = 0;
    for(size_t i = 0; i < bus_route.size() - 1; ++i){
       int length1 = 0, length2 = 0;

       // Check first connection
        if (stops.at(bus_route[i]).neighbors.count(bus_route[i + 1])) {
            length1 = stops.at(bus_route[i]).neighbors.at(bus_route[i + 1]);
        }
        
        // Check second connection
        if (stops.at(bus_route[i + 1]).neighbors.count(bus_route[i])) {
            length2 = stops.at(bus_route[i + 1]).neighbors.at(bus_route[i]);
        }
        if(is_roundtrip){
             if (length1 > 0) {
                total_length += length1;
            } else {
                total_length += length2;
            }

        } else {

            if (length1 > 0 && length2 > 0) {
                total_length += length1 + length2;
            } else {
                total_length += (length1 > 0) ? length1 * 2 : length2 * 2;
            }

        }

    }
    return total_length;
}

void Database::AddBus(std::string bus_id, std::vector<std::string> stops,bool is_roundtrip){
    bus_db.emplace(std::move(bus_id), Descriptions::BusInformation(std::move(stops),is_roundtrip));
};



std::optional<std::reference_wrapper<const Descriptions::BusInformation>> Database::GetBusInfo(const std::string& bus_id) const {
    auto it = bus_db.find(bus_id);
    if (it != bus_db.end()) {
        return it->second;
    }
    return std::nullopt;
};



/*Database Stop*/
void Database::AddStop(std::string stop_name, Descriptions::Coordinates coordinates, std::unordered_map<std::string, int> neighbors){
    stop_db.emplace(std::move(stop_name), Descriptions::StopInformation(coordinates, neighbors));
};


std::optional<std::reference_wrapper<const Descriptions::StopInformation>> Database::GetStopInfo(const std::string& stop_name) const{
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
        int total_stops = bus_info.is_roundtrip ? CalculateTotalStops(stops_list) : CalculateTotalStops(stops_list) * 2 - 1;
        /*Unique stops*/
        int unique_stops_count = CalculateUniqueStops(stops_list);

        /*Total length Coordinates*/
        double total_length = CalculateTotalLengthCoordinates(stop_db, stops_list, bus_info.is_roundtrip);

        /*Total length stops*/
        int total_length_stops = CalculateTotalLengthStops(stop_db, stops_list, bus_info.is_roundtrip);

        /*Curvature*/
        double curvature = total_length_stops / total_length;


        /* Update */
        bus_info.stops = total_stops;
        bus_info.unique_stops = unique_stops_count;
        bus_info.route_len = total_length_stops;
        bus_info.curvature = curvature;
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


void Database::UpdateStats(){
    UpdateBusStats();
    UpdateStopStats();
};


};

/*Database Bus*/


