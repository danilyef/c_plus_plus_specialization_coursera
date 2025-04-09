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
    void SetRenderSettings(const Json::Node& render_settings_node);
    void SetMinCoordinates(const Descriptions::Coordinates& coordinates);
    void SetMaxCoordinates(const Descriptions::Coordinates& coordinates);

    void CalculateZoomCoef();
    Svg::Point ProjectCoordinates(const Descriptions::Coordinates& coordinates) const;
    
    using BusDatabase = std::map<std::string, Descriptions::BusInformation>;
    using StopDatabase = std::map<std::string, Descriptions::StopInformation>;
    
    void RenderBusLines(const BusDatabase& bus_db, const StopDatabase& stop_db);
    void RenderCoordinates(const StopDatabase& stop_db);
    void RenderStopsNames(const StopDatabase& stop_db);
    void RenderBusLabels(const BusDatabase& bus_db, const StopDatabase& stop_db);
    
    const Svg::Document& GetMap() const;
    const Descriptions::RenderSettings& GetRenderSettings() const;
        
private:
    Svg::Document map_;
    Descriptions::RenderSettings render_settings;

    void RenderBusLabel(const std::string& bus_name, size_t color_index, 
                       const std::string& stop_name, const StopDatabase& stop_db);
};


