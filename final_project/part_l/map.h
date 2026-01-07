#pragma once

#include "types.h"
#include "json.h"
#include "svg.h"
#include <map>
#include <string>
#include <stdexcept>
#include <unordered_set>


Descriptions::Layer LayersMapping(const std::string& str);


class Map {
public:

    using BusDatabase = std::map<std::string, Descriptions::BusInformation>;
    using StopDatabase = std::map<std::string, Descriptions::StopInformation>;

    void SetRenderSettings(const Json::Node& render_settings_node);

    void DetermineIntermidiateStops(const BusDatabase& bus_db);

    void CalculateRenderCoordinates(BusDatabase& bus_db, StopDatabase& stop_db);
    void CreateCoordinatesMapping(StopDatabase& stop_db, const BusDatabase& bus_db);

    void CalculateStepsForCoordinatesMapping();
    void SetStepX();
    void SetStepY();

    
    void RenderBusLines(const BusDatabase& bus_db, const StopDatabase& stop_db);
    void RenderCoordinates(const StopDatabase& stop_db);
    void RenderStopsNames(const StopDatabase& stop_db);
    void RenderBusLabels(const BusDatabase& bus_db, const StopDatabase& stop_db);

    Svg::Point CoordinatesProjection(const Descriptions::Coordinates& coordinates);
    
    const Svg::Document& GetMap() const;
    const Descriptions::RenderSettings& GetRenderSettings() const;
        
private:
    Svg::Document map_;
    Descriptions::RenderSettings render_settings;
    std::unordered_map<double, size_t> lon_idx;
    std::unordered_map<double, size_t> lat_idx;
    size_t max_lon_idx;
    size_t max_lat_idx;
    std::unordered_set<std::string> core_stops;

    void RenderBusLabel(const std::string& bus_name, size_t color_index, 
                       const std::string& stop_name, const StopDatabase& stop_db);
                       
    size_t AssignCoordinateIndices(const std::vector<std::pair<std::string, double>>& coords, 
                            std::unordered_map<double, size_t>& idx_map,
                            const StopDatabase& stop_db,
                            std::unordered_map<std::string_view, std::set<std::string_view>>& neighbours);

    
    //Render coordinates
    void CalculateCoreStops(const BusDatabase& bus_db, const StopDatabase& stop_db);
    std::vector<size_t> CalculateCoreStopsIndices(const Descriptions::BusInformation& bus_info);
    void SetCoreStopsRenderCoordinates(StopDatabase& stop_db);
    void ProcessBusRoutesRenderCoordinates(BusDatabase& bus_db, StopDatabase& stop_db);
    void ProcessBusSegmentsRenderCoordinates(const Descriptions::BusInformation& bus_info, 
                           const std::vector<size_t>& core_stops_indices, 
                           StopDatabase& stop_db);
    void InterpolateSegmentRenderCoordinates(const Descriptions::BusInformation& bus_info, 
                                      size_t start_idx, size_t end_idx, 
                                      StopDatabase& stop_db);
    void SetNonBusStopsRenderCoordinates(StopDatabase& stop_db);

};


