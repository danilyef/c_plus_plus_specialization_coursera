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

void Map::SetStepX() {
    if (lon_idx.size() == 1) {
        render_settings.step_x = 0.0;
    } else {
        render_settings.step_x = (render_settings.width - 2.0 * render_settings.padding) / max_lon_idx;
    }
}

void Map::SetStepY() {
    if (lat_idx.size() == 1) {
        render_settings.step_y = 0.0;
    } else {
        render_settings.step_y = (render_settings.height - 2.0 * render_settings.padding) / max_lat_idx;
    }
}

void Map::CalculateStepsForCoordinatesMapping() {
    SetStepX();
    SetStepY();
}


void Map::CreateCoordinatesMapping(StopDatabase& stop_db, const BusDatabase& bus_db) {
    std::unordered_map<std::string, std::set<std::string>> neighbors;
    
    for (const auto& [bus_name, bus] : bus_db) {
        const auto& stops = bus.bus_stops;
        
        for (size_t i = 1; i < stops.size(); i++) {
            const std::string& from = stops[i - 1];
            const std::string& to = stops[i];

            neighbors[from].insert(to);
            neighbors[to].insert(from);
        }
    }

    std::vector<std::pair<std::string, double>> longitudes, latitudes;
    longitudes.reserve(stop_db.size());
    latitudes.reserve(stop_db.size());

    for (const auto& [name, stop] : stop_db) {
        longitudes.emplace_back(name, stop.coordinates.longitude);
        latitudes.emplace_back(name, stop.coordinates.latitude);
    }

    auto compareByCoordinate = [](const auto& a, const auto& b) {
        return a.second < b.second;
    };
    
    std::sort(longitudes.begin(), longitudes.end(), compareByCoordinate);
    std::sort(latitudes.begin(), latitudes.end(), compareByCoordinate);

    max_lon_idx = AssignCoordinateIndices(longitudes, lon_idx, stop_db, neighbors);
    max_lat_idx = AssignCoordinateIndices(latitudes, lat_idx, stop_db, neighbors);
}

size_t Map::AssignCoordinateIndices(
    const std::vector<std::pair<std::string, double>>& coords,
    std::unordered_map<double, size_t>& idx_map,
    const StopDatabase& stop_db,
    std::unordered_map<std::string, std::set<std::string>>& neighbors) {
    
    if (coords.empty()) {
        return 0;
    }
    
    size_t current_idx = 0;
    idx_map[coords[0].second] = current_idx;
    
    for (size_t i = 1; i < coords.size(); i++) {
        const auto& current_stop_name = coords[i].first;
        const auto& current_coordinate = coords[i].second;
        
        bool has_route_neighbor = false;
        
        for (int j = static_cast<int>(i) - 1; j >= 0; j--) {
            if (idx_map[coords[j].second] != current_idx) {
                break;
            }
            
            const auto& prev_stop_name = coords[j].first;
            
            if (neighbors[current_stop_name].count(prev_stop_name) > 0) {
                has_route_neighbor = true;
                break;
            }
        }
        
        if (has_route_neighbor) {
            current_idx++;
        }
        
        idx_map[current_coordinate] = current_idx;
    }
    
    return current_idx;
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