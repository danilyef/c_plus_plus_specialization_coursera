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

std::optional<size_t> TransportRouter::GetStopToId(const std::string& stop_name) const{
    const auto it = stop_to_id_map.find(stop_name);
    if(it != stop_to_id_map.end()){
        return it->second;
    }
    return std::nullopt;
}

/*Other*/
std::pair<size_t,size_t>  TransportRouter::AddWaitTimeEdge(const std::string& stop_name){
    size_t id = stop_to_id_map.size();
    if (stop_to_id_map.find(stop_name) == stop_to_id_map.end()){
        stop_to_id_map.insert({stop_name + "_wait", id});
        stop_to_id_map.insert({stop_name, id + 1});

        route_db.emplace(std::make_pair(id, id + 1), Descriptions::Wait{GetWaitTime(), stop_name, "Wait"});
        graph.AddEdge({id, id + 1, GetWaitTime()});
        
        return {id, id + 1};
    } 
    
    return {stop_to_id_map[stop_name + "_wait"],stop_to_id_map[stop_name]};

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
        return std::move(route_info);
    } 
    
    return std::nullopt;
}