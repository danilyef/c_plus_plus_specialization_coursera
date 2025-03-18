#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <functional>
#include "types.h"


namespace DatabaseStats {
    const double DEG_TO_RAD = 3.1415926535 / 180.0;
    double ComputeDistanceCoordinates(const Descriptions::Coordinates& lhs, const Descriptions::Coordinates& rhs);
    int CalculateUniqueStops(const std::vector<std::string>& stops);
    int CalculateTotalStops(const std::vector<std::string>& stops);
    double CalculateTotalLength(const std::unordered_map<std::string, Descriptions::Coordinates>& stops, const std::vector<std::string>& bus_route, bool is_roundtrip); 
    double CalculateTotalLengthCoordinates(const std::unordered_map<std::string, Descriptions::StopInformation>& stops, const std::vector<std::string>& bus_route, bool is_roundtrip);
    int CalculateTotalLengthStops(const std::unordered_map<std::string, Descriptions::StopInformation>& stops, const std::vector<std::string>& bus_route, bool is_roundtrip);


class Database {


public:

    /*Getters*/
    std::optional<std::reference_wrapper<const Descriptions::BusInformation>> GetBusInfo(const std::string& bus_id) const;
    std::optional<std::reference_wrapper<const Descriptions::StopInformation>> GetStopInfo(const std::string& stop_name) const;
    
    /*Setters*/
    void AddBus(std::string bus_id, std::vector<std::string> stops,bool is_roundtrip);
    void AddStop(std::string stop_name, Descriptions::Coordinates coordinates, std::unordered_map<std::string, int> neighbors = {});

    /*Update*/
    void UpdateStats();

private:
    std::unordered_map<std::string,Descriptions::BusInformation> bus_db;
    std::unordered_map<std::string,Descriptions::StopInformation> stop_db;

    /*Stats*/
    void UpdateBusStats();
    void UpdateStopStats();
    
};

};



