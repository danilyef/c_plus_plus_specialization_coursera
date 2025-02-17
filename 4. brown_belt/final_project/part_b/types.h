#pragma once

#include <set>
#include <vector>
#include <string>

struct Coordinates {
    double latitude;
    double longitude;
};

struct BusInformation{
    BusInformation() : bus_stops(), stops(0), unique_stops(0), route_len(0), found(false), is_backandforth(false), curvature(0) {};
    BusInformation(std::vector<std::string> bus_stops,bool is_backandforth) : bus_stops(std::move(bus_stops)), stops(0), unique_stops(0), route_len(0), found(false), is_backandforth(is_backandforth), curvature(0) {};
    std::vector<std::string> bus_stops;
    size_t stops;
    size_t unique_stops;
    double route_len;
    bool is_backandforth;
    bool found;
    double curvature;
};


struct StopInformation{
    StopInformation() : buses(), coordinates(), neighbors(), found(false) {};
    StopInformation(Coordinates coordinates) : buses(), coordinates(std::move(coordinates)), neighbors(), found(true) {};
    StopInformation(Coordinates coordinates, std::unordered_map<std::string, int> neighbors) : buses(), coordinates(std::move(coordinates)), neighbors(std::move(neighbors)), found(true) {};
    std::set<std::string> buses;
    Coordinates coordinates;
    std::unordered_map<std::string, int> neighbors;
    bool found;
};


inline bool operator==(const BusInformation& lhs, const BusInformation& rhs) {
    return lhs.bus_stops == rhs.bus_stops && lhs.stops == rhs.stops && lhs.unique_stops == rhs.unique_stops && lhs.route_len == rhs.route_len;
}



