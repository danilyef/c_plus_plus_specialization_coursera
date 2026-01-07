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

void Map::DetermineIntermidiateStops(const BusDatabase& bus_db) {
    
}

void Map::CreateCoordinatesMapping(StopDatabase& stop_db, const BusDatabase& bus_db) {
    std::unordered_map<std::string_view, std::set<std::string_view>> neighbors;
    
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
        longitudes.emplace_back(name, stop.render_coordinates.longitude);
        latitudes.emplace_back(name, stop.render_coordinates.latitude);
    }

    auto compareByCoordinate = [](const auto& a, const auto& b) {
        return a.second < b.second;
    };
    
    std::sort(longitudes.begin(), longitudes.end(), compareByCoordinate);
    std::sort(latitudes.begin(), latitudes.end(), compareByCoordinate);

    max_lon_idx = AssignCoordinateIndices(longitudes, lon_idx, stop_db, neighbors, false);
    max_lat_idx = AssignCoordinateIndices(latitudes, lat_idx, stop_db, neighbors, true);
}

size_t Map::AssignCoordinateIndices(
    const std::vector<std::pair<std::string, double>>& coords,
    std::unordered_map<double, size_t>& idx_map,
    const StopDatabase& stop_db,
    std::unordered_map<std::string_view, std::set<std::string_view>>& neighbors,
    bool is_latitude) {
    
    if (coords.empty()) {
        return 0;
    }
    
    size_t current_idx = 0;
    size_t max_idx = 0;  // Track maximum index assigned
    idx_map[coords[0].second] = current_idx;
    
    for (size_t i = 1; i < coords.size(); i++) {
        const auto& current_stop_name = coords[i].first;
        const auto& current_coordinate = coords[i].second;
        std::set<std::string_view> stop_neighbors = neighbors[current_stop_name];

        std::vector<size_t> stop_neighbors_indices;
        for (const auto& neighbor : stop_neighbors) {
            Descriptions::Coordinates neighbor_coordinates = stop_db.at(std::string(neighbor)).render_coordinates;
            double neighbor_coord = is_latitude ? neighbor_coordinates.latitude : neighbor_coordinates.longitude;
            
            if(neighbor_coord < current_coordinate) {
                stop_neighbors_indices.push_back(idx_map.at(neighbor_coord));
            }
        }

        if (!stop_neighbors_indices.empty()) {
            size_t maxVal = *std::max_element(stop_neighbors_indices.begin(), stop_neighbors_indices.end());
            current_idx = maxVal + 1;
        } else {
            current_idx = 0;
        }

        idx_map[current_coordinate] = current_idx;
        max_idx = std::max(max_idx, current_idx); 
    }
    
    return max_idx; 
}

void Map::CalculateCoreStops(const BusDatabase& bus_db, const StopDatabase& stop_db) {


    for (const auto& [bus_name, bus_info] : bus_db) {
        // Add terminal stops
        core_stops.insert(bus_info.bus_stops.front());
        if (!bus_info.is_roundtrip && !bus_info.bus_stops.empty()) {
            core_stops.insert(bus_info.bus_stops.back());
        }

        // Count stop occurrences and add intersection points
        std::unordered_map<std::string, size_t> stop_count;
        for (const auto& stop_name : bus_info.bus_stops) {
            // Add stops that are part of multiple routes
            if (stop_db.at(stop_name).buses.size() > 1) {
                core_stops.insert(stop_name);
            }
            stop_count[stop_name]++;
        }

        // Add stops that appear multiple times in the route
        const size_t frequency_threshold = bus_info.is_roundtrip ? 2 : 1;
        for (const auto& [stop_name, count] : stop_count) {
            if (count > frequency_threshold) {
                core_stops.insert(stop_name);
            }
        }
    }
}

std::vector<size_t> Map::CalculateCoreStopsIndices(const Descriptions::BusInformation& bus_info) {
    std::vector<size_t> core_stops_indices;
    for (size_t i = 0; i < bus_info.bus_stops.size(); ++i) {
        const auto& stop_name = bus_info.bus_stops[i];
        if (core_stops.count(stop_name) > 0) {
            core_stops_indices.push_back(i);
        }
    }
    return core_stops_indices;
}    


void Map::CalculateRenderCoordinates(BusDatabase& bus_db, StopDatabase& stop_db) {
    CalculateCoreStops(bus_db, stop_db);
    SetCoreStopsRenderCoordinates(stop_db);
    ProcessBusRoutesRenderCoordinates(bus_db, stop_db);
    SetNonBusStopsRenderCoordinates(stop_db);
}

void Map::SetCoreStopsRenderCoordinates(StopDatabase& stop_db) {
    for (const auto& stop_name : core_stops) {
        stop_db.at(stop_name).render_coordinates = stop_db.at(stop_name).coordinates;
    }
}

void Map::ProcessBusRoutesRenderCoordinates(BusDatabase& bus_db, StopDatabase& stop_db) {
    for (auto& [bus_name, bus_info] : bus_db) {
        auto core_stops_indices = CalculateCoreStopsIndices(bus_info);

        if (bus_info.bus_stops.empty()) {
            continue;  // Skip empty routes
        }

        if (core_stops_indices.size() <= 1) {
            const auto& reference_coordinates = stop_db.at(bus_info.bus_stops[0]).coordinates;
            for (const auto& stop_name : bus_info.bus_stops) {
                stop_db.at(stop_name).render_coordinates = reference_coordinates;
            }
            continue;
        }
        ProcessBusSegmentsRenderCoordinates(bus_info, core_stops_indices, stop_db);
    }
}


void Map::ProcessBusSegmentsRenderCoordinates(const Descriptions::BusInformation& bus_info, 
                           const std::vector<size_t>& core_stops_indices, 
                           StopDatabase& stop_db) {
    // Process segments between core stops
    for (size_t i = 0; i < core_stops_indices.size() - 1; i++) {
        const size_t start_idx = core_stops_indices[i];
        const size_t end_idx = core_stops_indices[i + 1];
        
        if (start_idx >= end_idx || end_idx >= bus_info.bus_stops.size()) {
            continue;  // Skip invalid indices
        }

        InterpolateSegmentRenderCoordinates(bus_info, start_idx, end_idx, stop_db);
    }
}

void Map::InterpolateSegmentRenderCoordinates(const Descriptions::BusInformation& bus_info,
                                      size_t start_idx, size_t end_idx, 
                                      StopDatabase& stop_db) {
    const auto& start_stop = stop_db.at(bus_info.bus_stops[start_idx]);
    const auto& end_stop = stop_db.at(bus_info.bus_stops[end_idx]);
    
    // Calculate coordinate steps between core stops
    const double segment_length = static_cast<double>(end_idx - start_idx);
    const Descriptions::Coordinates steps = {
        (end_stop.coordinates.latitude - start_stop.coordinates.latitude) / segment_length,
        (end_stop.coordinates.longitude - start_stop.coordinates.longitude) / segment_length
    };

    // Interpolate coordinates for intermediate stops
    for (size_t k = start_idx + 1; k < end_idx; k++) {
        const double offset = static_cast<double>(k - start_idx);
        stop_db.at(bus_info.bus_stops[k]).render_coordinates = {
            start_stop.coordinates.latitude + steps.latitude * offset,
            start_stop.coordinates.longitude + steps.longitude * offset
        };
    }
}

void Map::SetNonBusStopsRenderCoordinates(StopDatabase& stop_db) {
    for (auto& [stop_name, stop_info] : stop_db) {
        if(stop_info.buses.size() == 0) {
            stop_info.render_coordinates = stop_info.coordinates;
        }
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
            polyline.AddPoint(CoordinatesProjection(stop_db.at(stop).render_coordinates));
        }
        
        if (!bus_info.is_roundtrip && bus_info.bus_stops.size() > 1) {
            for (int i = static_cast<int>(bus_info.bus_stops.size()) - 2; i >= 0; --i) {
                polyline.AddPoint(CoordinatesProjection(stop_db.at(bus_info.bus_stops[i]).render_coordinates));
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
            .SetCenter(CoordinatesProjection(stop_info.render_coordinates))

        );
    }
}

void Map::RenderStopsNames(const StopDatabase& stop_db) {
    for (const auto& [stop_name, stop_info] : stop_db) {
        const auto point = CoordinatesProjection(stop_info.render_coordinates);
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
    const auto point = CoordinatesProjection(stop_db.at(stop_name).render_coordinates);
    
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