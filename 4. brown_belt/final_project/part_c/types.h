#pragma once

#include <set>
#include <vector>
#include <string>

namespace Descriptions {

struct Coordinates {
    double latitude;
    double longitude;
};

struct BusInformation{
    BusInformation(std::vector<std::string> bus_stops,bool is_roundtrip) : bus_stops(std::move(bus_stops)), stops(0), unique_stops(0), route_len(0), is_roundtrip(is_roundtrip), curvature(0) {};
    std::vector<std::string> bus_stops;
    int stops;
    int unique_stops;
    double route_len;
    bool is_roundtrip;
    double curvature;
};


struct StopInformation{
    StopInformation(Coordinates coordinates) : buses(), coordinates(std::move(coordinates)), neighbors() {};
    StopInformation(Coordinates coordinates, std::unordered_map<std::string, int> neighbors) : buses(), coordinates(std::move(coordinates)), neighbors(std::move(neighbors)) {};
    std::set<std::string> buses;
    Coordinates coordinates;
    std::unordered_map<std::string, int> neighbors;
};


inline bool operator==(const BusInformation& lhs, const BusInformation& rhs) {
    return lhs.bus_stops == rhs.bus_stops && lhs.stops == rhs.stops && lhs.unique_stops == rhs.unique_stops && lhs.route_len == rhs.route_len;
}



};

