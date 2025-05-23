#pragma once

#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <string>
#include <functional>
#include "types.h"
#include "transport_router.h"
#include "map.h"
#include <limits>


namespace DatabaseStats {
    const double DEG_TO_RAD = 3.1415926535 / 180.0;
    double ComputeDistanceCoordinates(const Descriptions::Coordinates& lhs, const Descriptions::Coordinates& rhs);
    int CalculateUniqueStops(const std::vector<std::string>& stops);
    int CalculateTotalStops(const std::vector<std::string>& stops);
    double CalculateTotalLength(const std::map<std::string, Descriptions::Coordinates>& stops, const std::vector<std::string>& bus_route, bool is_roundtrip); 
    double CalculateTotalLengthCoordinates(const std::map<std::string, Descriptions::StopInformation>& stops, const std::vector<std::string>& bus_route, bool is_roundtrip);
    int CalculateTotalLengthStops(const std::map<std::string, Descriptions::StopInformation>& stops, const std::vector<std::string>& bus_route, bool is_roundtrip);
};


struct RouteLoopParams {
    int start_idx;
    int end_idx;
    int step;
};


class Database {


public:
    Database(size_t vertex_count);

    void InitializeRouter();

    /*Getters*/
    std::optional<std::reference_wrapper<const Descriptions::BusInformation>> GetBusInfo(const std::string& bus_id) const;
    std::optional<std::reference_wrapper<const Descriptions::StopInformation>> GetStopInfo(const std::string& stop_name) const;
    
    /*Setters*/
    void AddBus(std::string bus_id, std::vector<std::string> stops,bool is_roundtrip);
    void AddStop(std::string stop_name, Descriptions::Coordinates coordinates, std::unordered_map<std::string, int> neighbors = {});

    /*Update*/
    void UpdateDatabase();
    void RenderMap();

    /*Transport Router Access*/
    const std::optional<std::vector<Descriptions::RouteInfo>> BuildRoute(const std::string& from, const std::string& to) const;
    void SetRoutingSettings(const Json::Node& routing_settings_node);
    
    /*Map Access*/
    const Svg::Document& GetMap() const;
    void SetRenderSettings(const Json::Node& render_settings_node);

private:
    std::map<std::string,Descriptions::BusInformation> bus_db;
    std::map<std::string,Descriptions::StopInformation> stop_db;
    std::unique_ptr<TransportRouter> transport_router;
    Map map;

    /*Stats*/
    void UpdateBusStats();
    void UpdateStopStats();
    void UpdateMappingCoordinates();

    /*Functions related to graph building*/
    void BuildGraph();
    void ForwardPass(const std::string& bus_id, const Descriptions::BusInformation& bus_info);
    void BackwardPass(const std::string& bus_id, const Descriptions::BusInformation& bus_info);
    void ProcessSingleBusRoute(const std::string& bus_id, const Descriptions::BusInformation& bus_info, bool is_forward);
    void ProcessSingleStop(const std::string& bus_id, const std::string& from_stop, const std::vector<std::string>& stops, int current_pos, const RouteLoopParams& params);



    double CalculateTimeBetweenStops(const std::string& from_stop, const std::string& to_stop);
};




