#include "database.h"
#include <iostream>
#include <cmath>

namespace DatabaseStats {


double ComputeTime(int distance, double velocity){
    return (distance / velocity) * 60.0;
}


double ComputeDistanceCoordinates(const Descriptions::Coordinates& lhs, const Descriptions::Coordinates& rhs) {
    /*to radians */
    double lat1_rad = lhs.latitude * DEG_TO_RAD;
    double lon1_rad = lhs.longitude * DEG_TO_RAD;
    double lat2_rad = rhs.latitude * DEG_TO_RAD;
    double lon2_rad = rhs.longitude * DEG_TO_RAD;

    /*Calculate distance by formula*/
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

       /*first connection*/
        if (stops.at(bus_route[i]).neighbors.count(bus_route[i + 1])) {
            length1 = stops.at(bus_route[i]).neighbors.at(bus_route[i + 1]);
        }
        
        /*second connection*/
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

Database::Database(size_t vertex_count) : transport_router(vertex_count){};

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


void Database::UpdateDatabase(){
    UpdateBusStats();
    UpdateStopStats();
    BuildGraph();
};


void Database::InitializeRouter(){
    transport_router.SetRouter(transport_router.GetGraph());
}


void Database::BuildGraph(){
    Graph::DirectedWeightedGraph<double>& graph = transport_router.GetGraph();

    for (const auto& [bus_id, bus_info] : bus_db) {
        ForwardPass(bus_id, bus_info, graph);
        
        if (!bus_info.is_roundtrip) {
            BackwardPass(bus_id, bus_info, graph);
        }
    }
}

void Database::ForwardPass(const std::string& bus_id, const Descriptions::BusInformation& bus_info, Graph::DirectedWeightedGraph<double>& graph) {
    ProcessBusRoute(bus_id, bus_info, graph, true);
}

void Database::BackwardPass(const std::string& bus_id, const Descriptions::BusInformation& bus_info, Graph::DirectedWeightedGraph<double>& graph) {
    ProcessBusRoute(bus_id, bus_info, graph, false);
}


RouteLoopParams GetLoopParams(bool is_forward, int stop_count) {
    return {
        .start_idx = is_forward ? 0 : stop_count - 1,
        .end_idx = is_forward ? stop_count : -1,
        .step = is_forward ? 1 : -1
    };
}

std::pair<Graph::VertexId, Graph::VertexId> Database::AddRouteEdge(
    const std::pair<Graph::VertexId, Graph::VertexId>& from_vertex_pair,
    const std::string& to_stop,
    double total_route_time,
    Graph::DirectedWeightedGraph<double>& graph,
    int span_count) {
    
    auto to_vertex_pair = transport_router.AddWaitTimeEdge(to_stop);
    graph.AddEdge({from_vertex_pair.second, to_vertex_pair.first, total_route_time});
    
    return to_vertex_pair;
}

void Database::ProcessSingleStop(
    const std::string& bus_id,
    const std::string& from_stop,
    const std::vector<std::string>& stops,
    int current_pos,
    const RouteLoopParams& params,
    Graph::DirectedWeightedGraph<double>& graph) {
    
    auto from_vertex_pair = transport_router.AddWaitTimeEdge(from_stop);
    double total_route_time = 0.0;
    int span_count = 0;
    
    for (int j = current_pos + params.step; j != params.end_idx; j += params.step) {
        const std::string& to_stop = stops[j];
        const std::string& prev_stop = stops[j - params.step];
        
        double segment_time = CalculateTimeBetweenStops(prev_stop, to_stop);
        total_route_time += segment_time;
        span_count++;
        
        auto to_vertex_pair = AddRouteEdge(from_vertex_pair, to_stop, total_route_time, graph, span_count);
        transport_router.AddRouteInfo(std::make_pair(from_vertex_pair.second, to_vertex_pair.first),Descriptions::StopRoute{total_route_time, bus_id, span_count, "Bus"});
    }
}



void Database::ProcessBusRoute(
    const std::string& bus_id, 
    const Descriptions::BusInformation& bus_info, 
    Graph::DirectedWeightedGraph<double>& graph,
    bool is_forward) {
    
    if (bus_id.empty()) {
        throw std::invalid_argument("Bus ID cannot be empty");
    }
    if (bus_info.bus_stops.empty()) {
        throw std::invalid_argument("Bus route cannot be empty");
    }
    
    const auto& stops = bus_info.bus_stops;
    const int stop_count = stops.size();
    

    const RouteLoopParams params = GetLoopParams(is_forward, stop_count);
    
    for (int i = params.start_idx; i != params.end_idx; i += params.step) {
        const std::string& from_stop = stops[i];
        ProcessSingleStop(bus_id, from_stop, stops, i, params, graph);
    }
}

double Database::CalculateTimeBetweenStops(const std::string& from_stop, const std::string& to_stop) {
        if (stop_db.at(from_stop).neighbors.count(to_stop)) {
            int distance = stop_db.at(from_stop).neighbors.at(to_stop);
            return ComputeTime(distance, transport_router.GetVelocity());
        } else {
            int distance = stop_db.at(to_stop).neighbors.at(from_stop);
        return ComputeTime(distance, transport_router.GetVelocity());
    }
}

};




