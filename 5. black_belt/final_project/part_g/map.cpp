#include "map.h"



void Map::SetRenderSettings(const Json::Node&   render_settings_node){
    const auto& render_settings_map = render_settings_node.AsMap();
    render_settings.width = render_settings_map.at("width").AsDouble();
    render_settings.height = render_settings_map.at("height").AsDouble();
    render_settings.padding = render_settings_map.at("padding").AsDouble();
    render_settings.stop_radius = render_settings_map.at("stop_radius").AsDouble();
    render_settings.line_width = render_settings_map.at("line_width").AsDouble();
    render_settings.stop_label_font_size = render_settings_map.at("stop_label_font_size").AsInt();
    render_settings.underlayer_width = render_settings_map.at("underlayer_width").AsDouble();
    
    const auto& offset_array = render_settings_map.at("stop_label_offset").AsArray();
    for (const auto& offset_node : offset_array) {
        render_settings.stop_label_offset.push_back(offset_node.AsDouble());
    }
    
    const Json::Node& underlayer_color_info = render_settings_map.at("underlayer_color");
    render_settings.underlayer_color = Svg::Color::ToColor(underlayer_color_info);
    
    const auto& color_palette_info = render_settings_map.at("color_palette").AsArray();
    for (const auto& color_node : color_palette_info) {
        render_settings.color_palette.push_back(Svg::Color::ToColor(color_node));
    }
};

void Map::SetMaxCoordinates(Descriptions::Coordinates coordinates){
    render_settings.max_coordinates = coordinates;
}

void Map::SetMinCoordinates(Descriptions::Coordinates coordinates){
    render_settings.min_coordinates = coordinates;
}

void Map::CalculateZoomCoef(){
   
    const double width_zoom_coef_denominator = render_settings.max_coordinates.longitude - render_settings.min_coordinates.longitude;
    const double height_zoom_coef_denominator = render_settings.max_coordinates.latitude - render_settings.min_coordinates.latitude;
    const double available_space = render_settings.width - 2.0 * render_settings.padding;
    const double available_height = render_settings.height - 2.0 * render_settings.padding;
    const double epsilon = 1e-6;

    // Calculate zoom coefficients for both dimensions
    const double width_zoom_coef = std::abs(width_zoom_coef_denominator) < epsilon ? 0.0 : available_space / width_zoom_coef_denominator;
    const double height_zoom_coef = std::abs(height_zoom_coef_denominator) < epsilon ? 0.0 : available_height / height_zoom_coef_denominator;

    // Use the non-zero zoom coefficient, or 0 if both are zero
    render_settings.zoom_coef = (width_zoom_coef == 0.0) ? height_zoom_coef : 
                              (height_zoom_coef == 0.0) ? width_zoom_coef : 
                              std::min(width_zoom_coef, height_zoom_coef);
    
}


Svg::Point Map::ProjectCoordinates(const Descriptions::Coordinates& coordinates){
    return {
        (coordinates.longitude - render_settings.min_coordinates.longitude) * render_settings.zoom_coef + render_settings.padding,
        (render_settings.max_coordinates.latitude - coordinates.latitude) * render_settings.zoom_coef + render_settings.padding
    };
}


void Map::RenderBusLines(const std::map<std::string, Descriptions::BusInformation>& bus_db, const std::map<std::string, Descriptions::StopInformation>& stop_db){
    size_t color_index = 0;
    for (const auto& bus : bus_db){
        Svg::Polyline polyline{};
        polyline
            .SetStrokeColor(render_settings.color_palette[color_index])
            .SetStrokeWidth(render_settings.line_width)
            .SetStrokeLineCap("round")
            .SetStrokeLineJoin("round");
        for (const auto& stop : bus.second.bus_stops){
            polyline.AddPoint(ProjectCoordinates(stop_db.at(stop).coordinates));
        }
        color_index = (color_index + 1) % render_settings.color_palette.size();
        if (!bus.second.is_roundtrip){
           for (int i = bus.second.bus_stops.size() - 2; i >= 0; --i){
                polyline.AddPoint(ProjectCoordinates(stop_db.at(bus.second.bus_stops[i]).coordinates));
           }
        }
        map_.Add(polyline);
    }
}


void Map::RenderCoordinates(const std::map<std::string, Descriptions::StopInformation>& stop_db){
    for (const auto& stop : stop_db){
        map_.Add(
            Svg::Circle{}
            .SetFillColor("white")
            .SetRadius(render_settings.stop_radius)
            .SetCenter(ProjectCoordinates(stop.second.coordinates))
        );
    }
}


void Map::RenderStopsNames(const std::map<std::string, Descriptions::StopInformation>& stop_db){
    for (const auto& stop : stop_db){
        // Background
        map_.Add(
            Svg::Text{}
            .SetPoint(ProjectCoordinates(stop.second.coordinates))
            .SetOffset(Svg::Point{render_settings.stop_label_offset[0], render_settings.stop_label_offset[1]})
            .SetFontSize(render_settings.stop_label_font_size)
            .SetFontFamily("Verdana")
            .SetData(stop.first)
            .SetStrokeWidth(render_settings.underlayer_width)
            .SetStrokeLineCap("round")
            .SetStrokeLineJoin("round")
            .SetStrokeColor(render_settings.underlayer_color)
            .SetFillColor(render_settings.underlayer_color)
        );
        
        // Label itself
        map_.Add(
            Svg::Text{}
            .SetPoint(ProjectCoordinates(stop.second.coordinates))
            .SetOffset(Svg::Point{render_settings.stop_label_offset[0], render_settings.stop_label_offset[1]})
            .SetFontSize(render_settings.stop_label_font_size)
            .SetFontFamily("Verdana")
            .SetData(stop.first)
            .SetFillColor("black")
        );
    }
}


const Svg::Document& Map::GetMap() const{
    return map_;
}