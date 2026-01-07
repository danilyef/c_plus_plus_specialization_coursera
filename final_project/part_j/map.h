#pragma once

#include "types.h"
#include "json.h"
#include "svg.h"
#include <map>
#include <string>
#include <stdexcept>


Descriptions::Layer LayersMapping(const std::string& str);


class Map {
public:

    using BusDatabase = std::map<std::string, Descriptions::BusInformation>;
    using StopDatabase = std::map<std::string, Descriptions::StopInformation>;

    void SetRenderSettings(const Json::Node& render_settings_node);

    void CreateCoordinatesMapping(StopDatabase& stop_db);

    void CalculateStepsForCoordinatesMapping(const StopDatabase& stop_db);
    void SetStepX(const StopDatabase& stop_db);
    void SetStepY(const StopDatabase& stop_db);

    
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

    void RenderBusLabel(const std::string& bus_name, size_t color_index, 
                       const std::string& stop_name, const StopDatabase& stop_db);
};


