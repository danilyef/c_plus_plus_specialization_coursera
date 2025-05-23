#include "map.h"
#include "types.h" 
#include "json.h"
#include <cmath>
#include <algorithm>

Descriptions::Layer LayersMapping(const std::string& str) {
    if (str == "bus_lines") return Descriptions::Layer::BUS_LINES;
    if (str == "bus_labels") return Descriptions::Layer::BUS_LABELS;
    if (str == "stop_points") return Descriptions::Layer::STOP_POINTS;
    if (str == "stop_labels") return Descriptions::Layer::STOP_LABELS;
    std::string error_msg = str + "is unknown name for mapping layer type";
    throw std::runtime_error(error_msg);
}

void Map::SetRenderSettings(const Json::Node& render_settings_node) {
    const auto& render_settings_map = render_settings_node.AsMap();
    render_settings.width = render_settings_map.at("width").AsDouble();
    render_settings.height = render_settings_map.at("height").AsDouble();
    render_settings.padding = render_settings_map.at("padding").AsDouble();
    render_settings.stop_radius = render_settings_map.at("stop_radius").AsDouble();
    render_settings.line_width = render_settings_map.at("line_width").AsDouble();
    render_settings.stop_label_font_size = render_settings_map.at("stop_label_font_size").AsInt();
    render_settings.underlayer_width = render_settings_map.at("underlayer_width").AsDouble();
    
    const auto& offset_array = render_settings_map.at("stop_label_offset").AsArray();
    render_settings.stop_label_offset.reserve(offset_array.size());
    for (const auto& offset_node : offset_array) {
        render_settings.stop_label_offset.push_back(offset_node.AsDouble());
    }
    
    render_settings.underlayer_color = Svg::Color::ToColor(render_settings_map.at("underlayer_color"));
    
    const auto& color_palette_info = render_settings_map.at("color_palette").AsArray();
    render_settings.color_palette.reserve(color_palette_info.size());
    for (const auto& color_node : color_palette_info) {
        render_settings.color_palette.push_back(Svg::Color::ToColor(color_node));
    }
    
    render_settings.bus_label_font_size = render_settings_map.at("bus_label_font_size").AsInt();
    
    const auto& bus_label_offset_info = render_settings_map.at("bus_label_offset").AsArray();
    render_settings.bus_label_offset = Svg::Point{
        bus_label_offset_info[0].AsDouble(), 
        bus_label_offset_info[1].AsDouble()
    };

    const auto& layers_info = render_settings_map.at("layers").AsArray();
    render_settings.layers.reserve(layers_info.size());
    for (const auto& layer_node : layers_info) {
        render_settings.layers.push_back(LayersMapping(layer_node.AsString()));
    }
}

void Map::SetStepX(const StopDatabase& stop_db) {
    if (stop_db.size() == 1) {
        render_settings.step_x = 0.0;
    } else {
        render_settings.step_x = (render_settings.width - 2.0 * render_settings.padding) / (stop_db.size() - 1);
    }
}

void Map::SetStepY(const StopDatabase& stop_db) {
    if (stop_db.size() == 1) {
        render_settings.step_y = 0.0;
    } else {
        render_settings.step_y = (render_settings.height - 2.0 * render_settings.padding) / (stop_db.size() - 1);
    }
}

void Map::CalculateStepsForCoordinatesMapping(const StopDatabase& stop_db) {
    SetStepX(stop_db);
    SetStepY(stop_db);
}


void Map::CreateCoordinatesMapping(StopDatabase& stop_db) {
    
    std::vector<double> lons, lats;
    lons.reserve(stop_db.size());
    lats.reserve(stop_db.size());

    for (const auto& [name, stop] : stop_db) {
        lons.push_back(stop.coordinates.longitude);
        lats.push_back(stop.coordinates.latitude);
    }

    std::sort(lons.begin(), lons.end());
    std::sort(lats.begin(), lats.end());

    for (size_t i = 0; i < lons.size(); i++) {
        lon_idx[lons[i]] = i;
    }

    for (size_t i = 0; i < lats.size(); i++) {
        lat_idx[lats[i]] = i;
    }
}

Svg::Point Map::CoordinatesProjection(const Descriptions::Coordinates& coordinates) {
    double x = lon_idx[coordinates.longitude] * render_settings.step_x + render_settings.padding;
    double y = render_settings.height - render_settings.padding - lat_idx[coordinates.latitude] * render_settings.step_y;
    return {x, y};
}


void Map::RenderBusLines(const BusDatabase& bus_db, const StopDatabase& stop_db) {
    for (const auto& [bus_name, bus_info] : bus_db) {
        Svg::Polyline polyline;
        polyline
            .SetStrokeColor(render_settings.color_palette[bus_info.color_index])
            .SetStrokeWidth(render_settings.line_width)
            .SetStrokeLineCap("round")
            .SetStrokeLineJoin("round");
            
        for (const auto& stop : bus_info.bus_stops) {
            polyline.AddPoint(CoordinatesProjection(stop_db.at(stop).coordinates));
        }
        
        if (!bus_info.is_roundtrip && bus_info.bus_stops.size() > 1) {
            for (int i = static_cast<int>(bus_info.bus_stops.size()) - 2; i >= 0; --i) {
                polyline.AddPoint(CoordinatesProjection(stop_db.at(bus_info.bus_stops[i]).coordinates));
            }
        }
        
        map_.Add(std::move(polyline));
    }
}

void Map::RenderCoordinates(const StopDatabase& stop_db) {
    for (const auto& [stop_name, stop_info] : stop_db) {
        map_.Add(
            Svg::Circle{}
            .SetFillColor("white")
            .SetRadius(render_settings.stop_radius)
            .SetCenter(CoordinatesProjection(stop_info.coordinates))

        );
    }
}

void Map::RenderStopsNames(const StopDatabase& stop_db) {
    for (const auto& [stop_name, stop_info] : stop_db) {
        const auto point = CoordinatesProjection(stop_info.coordinates);
        const auto offset = Svg::Point{
            render_settings.stop_label_offset[0], 
            render_settings.stop_label_offset[1]
        };
        
        // Background text (outline)
        map_.Add(
            Svg::Text{}
            .SetPoint(point)
            .SetOffset(offset)
            .SetFontSize(render_settings.stop_label_font_size)
            .SetFontFamily("Verdana")
            .SetData(stop_name)
            .SetStrokeWidth(render_settings.underlayer_width)
            .SetStrokeLineCap("round")
            .SetStrokeLineJoin("round")
            .SetStrokeColor(render_settings.underlayer_color)
            .SetFillColor(render_settings.underlayer_color)
        );
        
        // Foreground text (label)
        map_.Add(
            Svg::Text{}
            .SetPoint(point)
            .SetOffset(offset)
            .SetFontSize(render_settings.stop_label_font_size)
            .SetFontFamily("Verdana")
            .SetData(stop_name)
            .SetFillColor("black")
        );
    }
}

void Map::RenderBusLabel(const std::string& bus_name, size_t color_index, 
                        const std::string& stop_name, const StopDatabase& stop_db) {
    const auto point = CoordinatesProjection(stop_db.at(stop_name).coordinates);
    
    // Background
    map_.Add(
        Svg::Text{}
        .SetPoint(point)
        .SetOffset(render_settings.bus_label_offset)
        .SetFontSize(render_settings.bus_label_font_size)
        .SetFontFamily("Verdana")
        .SetFontWeight("bold")
        .SetData(bus_name)
        .SetFillColor(render_settings.underlayer_color)
        .SetStrokeColor(render_settings.underlayer_color)
        .SetStrokeWidth(render_settings.underlayer_width)
        .SetStrokeLineCap("round")
        .SetStrokeLineJoin("round")
    );

    // Label itself
    map_.Add(
        Svg::Text{}
        .SetPoint(point)
        .SetOffset(render_settings.bus_label_offset)
        .SetFontSize(render_settings.bus_label_font_size)
        .SetFontFamily("Verdana")
        .SetFontWeight("bold")
        .SetData(bus_name)
        .SetFillColor(render_settings.color_palette[color_index])
    );
}

void Map::RenderBusLabels(const BusDatabase& bus_db, const StopDatabase& stop_db) {
    for (const auto& [bus_name, bus_info] : bus_db) {

        RenderBusLabel(bus_name, bus_info.color_index, bus_info.bus_stops.front(), stop_db);
            
        if (!bus_info.is_roundtrip && bus_info.bus_stops.size() > 1 && 
            bus_info.bus_stops.front() != bus_info.bus_stops.back()) {
            RenderBusLabel(bus_name, bus_info.color_index, bus_info.bus_stops.back(), stop_db);
        }
    }
}


const Descriptions::RenderSettings& Map::GetRenderSettings() const {
    return render_settings;
}

const Svg::Document& Map::GetMap() const {
    return map_;
}