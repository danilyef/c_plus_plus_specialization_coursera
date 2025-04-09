#pragma once

#include "graph.h"
#include "router.h"
#include "types.h"
#include <memory>
#include <iostream>
#include <utility>
#include "json.h"
#include "svg.h"


struct RouterDbHash {
    std::size_t operator()(const std::pair<size_t, size_t>& p) const {
        std::size_t h1 = std::hash<size_t>{}(p.first);
        std::size_t h2 = std::hash<size_t>{}(p.second);
        return h1 ^ (h2 * 31);  
    }
};


class TransportRouter{

public:

    /*Constructors*/
    TransportRouter(size_t vertex_count);

    /*Setters*/
    void SetRoutingSettings(Json::Node routing_settings_node);
    void SetRouter(const Graph::DirectedWeightedGraph<double>& graph);

    /*Getters*/
    const Graph::Router<double>* GetRouter() const;
    
    Graph::DirectedWeightedGraph<double>& GetGraph();
    const Graph::DirectedWeightedGraph<double>& GetGraph() const;

    double GetVelocity() const;
    double GetWaitTime() const;

    std::optional<Graph::VertexId> GetStopToId(const std::string& stop_name) const;

    /*Other*/
    std::pair<Graph::VertexId, Graph::VertexId> AddStopToId(const std::string& stop_name);
    const std::optional<std::vector<Descriptions::RouteInfo>> BuildRoute(const std::string& from, const std::string& to) const;
    void AddWaitTimeEdge(const Graph::VertexId& from_vertex, const Graph::VertexId& to_vertex);
    
    void AddRouteEdge(const Graph::VertexId& from_vertex, const Graph::VertexId& to_vertex, double total_route_time);
    void AddRouteInfo(std::pair<size_t, size_t> edge, Descriptions::RouteInfo route_info);


private:
    Graph::DirectedWeightedGraph<double> graph;
    std::unique_ptr<Graph::Router<double>> router;

    std::unordered_map<std::string, size_t> stop_to_id_map;
    std::unordered_map<std::pair<size_t, size_t>, Descriptions::RouteInfo, RouterDbHash> route_db;

    Descriptions::RoutingSettings routing_settings;
};



