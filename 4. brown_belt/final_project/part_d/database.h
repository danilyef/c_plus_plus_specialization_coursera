#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <functional>
#include "types.h"
#include "transport_router.h"


namespace DatabaseStats {
    const double DEG_TO_RAD = 3.1415926535 / 180.0;
    double ComputeDistanceCoordinates(const Descriptions::Coordinates& lhs, const Descriptions::Coordinates& rhs);
    int CalculateUniqueStops(const std::vector<std::string>& stops);
    int CalculateTotalStops(const std::vector<std::string>& stops);
    double CalculateTotalLength(const std::unordered_map<std::string, Descriptions::Coordinates>& stops, const std::vector<std::string>& bus_route, bool is_roundtrip); 
    double CalculateTotalLengthCoordinates(const std::unordered_map<std::string, Descriptions::StopInformation>& stops, const std::vector<std::string>& bus_route, bool is_roundtrip);
    int CalculateTotalLengthStops(const std::unordered_map<std::string, Descriptions::StopInformation>& stops, const std::vector<std::string>& bus_route, bool is_roundtrip);


struct RouteLoopParams {
    int start_idx;
    int end_idx;
    int step;
};


class Database {


public:
    Database(size_t vertex_count);
    TransportRouter transport_router;
    void InitializeRouter();

    /*Getters*/
    std::optional<std::reference_wrapper<const Descriptions::BusInformation>> GetBusInfo(const std::string& bus_id) const;
    std::optional<std::reference_wrapper<const Descriptions::StopInformation>> GetStopInfo(const std::string& stop_name) const;
    
    /*Setters*/
    void AddBus(std::string bus_id, std::vector<std::string> stops,bool is_roundtrip);
    void AddStop(std::string stop_name, Descriptions::Coordinates coordinates, std::unordered_map<std::string, int> neighbors = {});

    /*Update*/
    void UpdateDatabase();
    void BuildGraph();

private:
    std::unordered_map<std::string,Descriptions::BusInformation> bus_db;
    std::unordered_map<std::string,Descriptions::StopInformation> stop_db;

    /*Stats*/
    void UpdateBusStats();
    void UpdateStopStats();

    void ForwardPass(const std::string& bus_id, const Descriptions::BusInformation& bus_info, Graph::DirectedWeightedGraph<double>& graph);
    void BackwardPass(const std::string& bus_id, const Descriptions::BusInformation& bus_info, Graph::DirectedWeightedGraph<double>& graph);
    void ProcessBusRoute(const std::string& bus_id, const Descriptions::BusInformation& bus_info, Graph::DirectedWeightedGraph<double>& graph, bool is_forward);
    void ProcessSingleStop(const std::string& bus_id, const std::string& from_stop, const std::vector<std::string>& stops, int current_pos, const RouteLoopParams& params, Graph::DirectedWeightedGraph<double>& graph);
    std::pair<Graph::VertexId, Graph::VertexId>  AddRouteEdge(const std::pair<Graph::VertexId, Graph::VertexId>& from_vertex_pair, const std::string& to_stop, double total_route_time, Graph::DirectedWeightedGraph<double>& graph, int span_count);

    double CalculateTimeBetweenStops(const std::string& from_stop, const std::string& to_stop);
};

};



