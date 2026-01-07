#pragma once

#include "types.h"
#include "svg.h"
#include <cmath>
#include "json.h"


class Map{
    public:
        void SetRenderSettings(const Json::Node& render_settings_node);
        void SetMinCoordinates(Descriptions::Coordinates coordinates);
        void SetMaxCoordinates(Descriptions::Coordinates coordinates);


        void CalculateZoomCoef();
        Svg::Point ProjectCoordinates(const Descriptions::Coordinates& coordinates);
        void RenderBusLines(const std::map<std::string, Descriptions::BusInformation>& bus_db, const std::map<std::string, Descriptions::StopInformation>& stop_db);
        void RenderCoordinates(const std::map<std::string, Descriptions::StopInformation>& stop_db);
        void RenderStopsNames(const std::map<std::string, Descriptions::StopInformation>& stop_db);
        const Svg::Document& GetMap() const;

        
    private:
        Svg::Document map_;
        Descriptions::RenderSettings render_settings;

};


