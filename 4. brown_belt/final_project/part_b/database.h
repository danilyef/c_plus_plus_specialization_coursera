#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <functional>
#include "types.h"
#include "utils.h"


namespace Stats {
    size_t CalculateUniqueStops(const std::vector<std::string>& stops);
    size_t CalculateTotalStops(const std::vector<std::string>& stops);
    double CalculateTotalLength(const std::unordered_map<std::string, Coordinates>& stops, const std::vector<std::string>& bus_route); 
};

class Database {


public:

    /*Getters*/
    std::optional<std::reference_wrapper<const BusInformation>> GetBusInfo(const std::string& bus_id) const;
    std::optional<std::reference_wrapper<const StopInformation>> GetStopInfo(const std::string& stop_name) const;
    
    /*Setters*/
    void AddBus(std::string bus_id, std::vector<std::string> stops,bool is_backandforth);
    void AddStop(std::string stop_name, Coordinates coordinates, std::unordered_map<std::string, int> neighbors = {});

    /*Stats*/
    void UpdateBusStats();
    void UpdateStopStats();


private:
    std::unordered_map<std::string,BusInformation> bus_db;
    std::unordered_map<std::string,StopInformation> stop_db;
    
};


