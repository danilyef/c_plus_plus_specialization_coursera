#pragma once

#include <set>
#include <vector>
#include <string>
#include <variant>
#include <unordered_map>
#include <map>
#include "svg.h"

namespace Descriptions {

struct Coordinates {
    double latitude;
    double longitude;
};

struct BusInformation{
    BusInformation(std::vector<std::string> bus_stops,bool is_roundtrip) : bus_stops(std::move(bus_stops)), stops(0), unique_stops(0), route_len(0), is_roundtrip(is_roundtrip), curvature(0) {};
    std::vector<std::string> bus_stops;
    int stops;
    int unique_stops;
    double route_len;
    bool is_roundtrip;
    double curvature;
    size_t color_index;
};


struct StopInformation{
    StopInformation(Coordinates coordinates) : buses(), coordinates(std::move(coordinates)), neighbors() {};
    StopInformation(Coordinates coordinates, std::unordered_map<std::string, int> neighbors) : buses(), coordinates(std::move(coordinates)), neighbors(std::move(neighbors)) {};
    std::set<std::string> buses;
    Coordinates coordinates;
    Coordinates render_coordinates;
    std::unordered_map<std::string, int> neighbors;
};


inline bool operator==(const BusInformation& lhs, const BusInformation& rhs) {
    return lhs.bus_stops == rhs.bus_stops && lhs.stops == rhs.stops && lhs.unique_stops == rhs.unique_stops && lhs.route_len == rhs.route_len;
}

struct RoutingSettings{
    int bus_wait_time;
    int bus_velocity;
};


struct Wait{
   double time;
   std::string stop_name;
   std::string type;
};

struct StopRoute{
    double time;
    std::string bus_name;
    int span_count;
    std::string type;
};


using RouteInfo = std::variant<Wait, StopRoute>;

struct Map{
    std::string map;
    int request_id;
};


enum class Layer{
    BUS_LINES,
    BUS_LABELS,
    STOP_LABELS,
    STOP_POINTS
};

struct RenderSettings{
    double width;
    double height;
    double padding;
    double stop_radius;
    double line_width;
    int stop_label_font_size;
    std::vector<double> stop_label_offset;
    Svg::Color underlayer_color;
    double underlayer_width;
    std::vector<Svg::Color> color_palette;
    int bus_label_font_size;
    Svg::Point bus_label_offset;
    std::vector<Layer> layers;
    double step_x;
    double step_y;
};

};

