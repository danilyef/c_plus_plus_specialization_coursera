#include "transport_router.h"


/*Constructors*/
TransportRouter::TransportRouter(size_t vertex_count) : graph(vertex_count) {};

/*Setters*/
void TransportRouter::SetRoutingSettings(double bus_wait_time, double bus_velocity){
    routing_settings.bus_wait_time = bus_wait_time;
    routing_settings.bus_velocity = bus_velocity;
};


void TransportRouter::SetRouter(const Graph::DirectedWeightedGraph<double>& graph){
    router = std::make_unique<Graph::Router<double>>(graph);
}

/*Getters*/
double TransportRouter::GetVelocity() const{
    return routing_settings.bus_velocity;
};

double TransportRouter::GetWaitTime() const{
    return routing_settings.bus_wait_time;
};

Graph::DirectedWeightedGraph<double>& TransportRouter::GetGraph(){
    return graph;
};

const Graph::DirectedWeightedGraph<double>& TransportRouter::GetGraph() const{
    return graph;
};


const Graph::Router<double>* TransportRouter::GetRouter() const{
    return router.get();
}

std::optional<Graph::VertexId> TransportRouter::GetStopToId(const std::string& stop_name) const{
    const auto it = stop_to_id_map.find(stop_name);
    if(it != stop_to_id_map.end()){
        return it->second;
    }
    return std::nullopt;
}

std::pair<Graph::VertexId, Graph::VertexId> TransportRouter::AddStopToId(const std::string& stop_name){
    size_t id = stop_to_id_map.size();
    auto it_first = stop_to_id_map.try_emplace(stop_name + "_wait", id);
    auto it_second = stop_to_id_map.try_emplace(stop_name, id + 1);
    return {it_first.first->second, it_second.first->second};
}

/*Other*/
void TransportRouter::AddWaitTimeEdge(const Graph::VertexId& from_vertex, const Graph::VertexId& to_vertex){
        graph.AddEdge({from_vertex, to_vertex, GetWaitTime()});    
}


void TransportRouter::AddRouteEdge(
    const Graph::VertexId& from_vertex,
    const Graph::VertexId& to_vertex,
    double total_route_time) {
    
    graph.AddEdge({from_vertex, to_vertex, total_route_time});
    
}

void TransportRouter::AddRouteInfo(std::pair<size_t, size_t> edge, Descriptions::RouteInfo route_info){
    const auto it = route_db.find(edge);
    if (it != route_db.end()) {
        if (std::holds_alternative<Descriptions::StopRoute>(it->second) && std::get<Descriptions::StopRoute>(route_info).time < std::get<Descriptions::StopRoute>(it->second).time) {  
            route_db[edge] = std::move(route_info);
        } 
    } else {
        route_db.emplace(edge, std::move(route_info));
    }
    
}


const std::optional<std::vector<Descriptions::RouteInfo>> TransportRouter::BuildRoute(const std::string& from, const std::string& to) const{
    std::vector<Descriptions::RouteInfo> route_info;

    const auto start = GetStopToId(from);
    const auto end = GetStopToId(to);
    if(!start || !end){
        return std::nullopt;
    }

    const auto& route = router->BuildRoute(start.value(), end.value());
    if (route){
        for (size_t i = 0; i < route.value().edge_count; ++i) {
            const auto edge_id = router->GetRouteEdge(route.value().id, i);
            const auto& edge = graph.GetEdge(edge_id);
            route_info.push_back(route_db.at(std::make_pair(edge.from, edge.to)));
        }
        router->ReleaseRoute(route.value().id);
        return std::move(route_info);
    } 
    
    return std::nullopt;
}