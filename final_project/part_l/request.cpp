#include "request.h"


Request::Request(Type type): type_(type){};

/*ReadRequest*/
std::optional<Json::Node> ReadRequest::Process(Database& db) {
    return ProcessRead(db);
}

/*ModifyRequest*/
std::optional<Json::Node> ModifyRequest::Process(Database& db) {
    ProcessModify(db);
    return std::nullopt;
}


Json::Node ReadRequest::CreateNotFoundResponse(int request_id) const {
    return Json::Node(std::map<std::string,Json::Node>{
        {"request_id", Json::Node(request_id)},
        {"error_message", Json::Node(std::string("not found"))}
    });
}

/*AddStopRequest*/
void AddStopRequest::ParseFromNode(const Json::Node& node){
    stop_name = node.AsMap().at("name").AsString();
    coordinates.latitude = node.AsMap().at("latitude").AsDouble();
    coordinates.longitude = node.AsMap().at("longitude").AsDouble();
    for(const auto& neighbor: node.AsMap().at("road_distances").AsMap()){
        neighbors[neighbor.first] = neighbor.second.AsInt();
    }
}


AddStopRequest::AddStopRequest(): ModifyRequest(Type::ADD_STOP){};
    void AddStopRequest::ProcessModify(Database& db){
    if(neighbors.empty()){
        db.AddStop(std::move(stop_name), std::move(coordinates));
    } else {
        db.AddStop(std::move(stop_name), std::move(coordinates), std::move(neighbors));
    }

}


/*AddBusRequest*/
void AddBusRequest::ParseFromNode(const Json::Node& node){
    bus_id = node.AsMap().at("name").AsString();
    for(const auto& stop: node.AsMap().at("stops").AsArray()){
        stops.push_back(stop.AsString());
    }
    is_roundtrip = node.AsMap().at("is_roundtrip").AsBool();
}

AddBusRequest::AddBusRequest(): ModifyRequest(Type::ADD_BUS){};
void AddBusRequest::ProcessModify(Database& db){
    db.AddBus(std::move(bus_id), std::move(stops), is_roundtrip);
}


/*GetBusRequest*/
void GetBusRequest::ParseFromNode(const Json::Node& node){
    bus_id = node.AsMap().at("name").AsString();
    request_id = node.AsMap().at("id").AsInt();
}

Json::Node GetBusRequest::CreateSuccessResponse(int request_id, const Descriptions::BusInformation& busInfo) const {
    return Json::Node(std::map<std::string,Json::Node>{
        {"route_length", Json::Node(busInfo.route_len)},
        {"request_id", Json::Node(request_id)},
        {"curvature", Json::Node(busInfo.curvature)},
        {"stop_count", Json::Node(busInfo.stops)},
        {"unique_stop_count", Json::Node(busInfo.unique_stops)}
    });
}



GetBusRequest::GetBusRequest(): ReadRequest(Type::GET_BUS){};
Json::Node GetBusRequest::ProcessRead(const Database& db) const {
    const auto& bus = db.GetBusInfo(bus_id);
    if(bus){
        const Descriptions::BusInformation& busInfoObject = bus->get();
        return GetBusRequest::CreateSuccessResponse(request_id, busInfoObject);
    } 
    return CreateNotFoundResponse(request_id);
};


/*GetStopRequest*/
void GetStopRequest::ParseFromNode(const Json::Node& node){
    stop_name = node.AsMap().at("name").AsString();
    request_id = node.AsMap().at("id").AsInt();
}


Json::Node GetStopRequest::CreateSuccessResponse(int request_id, const Descriptions::StopInformation& stopInfo) const {
    std::vector<Json::Node> buses(stopInfo.buses.begin(), stopInfo.buses.end());
    return Json::Node(std::map<std::string,Json::Node>{
        {"buses", Json::Node(std::move(buses))},
        {"request_id", Json::Node(request_id)}
    });
}


GetStopRequest::GetStopRequest(): ReadRequest(Type::GET_STOP){};
Json::Node GetStopRequest::ProcessRead(const Database& db) const {
    const auto& stop = db.GetStopInfo(stop_name);
    if(stop){
        const Descriptions::StopInformation& stopInfoObject = stop->get();
        return GetStopRequest::CreateSuccessResponse(request_id, stopInfoObject);
    } 
    return CreateNotFoundResponse(request_id);
};


GetRouteRequest::GetRouteRequest(): ReadRequest(Type::GET_ROUTE){};
void GetRouteRequest::ParseFromNode(const Json::Node& node){
    from = node.AsMap().at("from").AsString() + "_wait";
    to = node.AsMap().at("to").AsString() + "_wait";
    request_id = node.AsMap().at("id").AsInt();
}

Json::Node GetRouteRequest::CreateWaitItem(const Descriptions::Wait& wait) const {
    return Json::Node(std::map<std::string,Json::Node>{
        {"type", Json::Node(wait.type)},
        {"time", Json::Node(wait.time)},
        {"stop_name", Json::Node(wait.stop_name)}
    });
}

Json::Node GetRouteRequest::CreateStopRouteItem(const Descriptions::StopRoute& route) const {
    return Json::Node(std::map<std::string,Json::Node>{
        {"type", Json::Node(route.type)},
        {"time", Json::Node(route.time)},
        {"bus", Json::Node(route.bus_name)},
        {"span_count", Json::Node(route.span_count)}
    });
}

std::pair<Json::Node, double> GetRouteRequest::ProcessRouteItems(const std::vector<Descriptions::RouteInfo>& route) const {
    std::vector<Json::Node> items;
    double total_time = 0.0;
    
    for(const auto& info : route) {
        if(std::holds_alternative<Descriptions::Wait>(info)) {
            const auto& wait = std::get<Descriptions::Wait>(info);
            items.push_back(GetRouteRequest::CreateWaitItem(wait));
            total_time += wait.time;
        } else if(std::holds_alternative<Descriptions::StopRoute>(info)) {
            const auto& stop_route = std::get<Descriptions::StopRoute>(info);
            items.push_back(GetRouteRequest::CreateStopRouteItem(stop_route));
            total_time += stop_route.time;
        }
    }
    return {Json::Node(std::move(items)), total_time};
}


Json::Node GetRouteRequest::CreateSuccessResponse(int request_id, Json::Node items, double total_time) const {
    return Json::Node(std::map<std::string,Json::Node>{
        {"total_time", Json::Node(total_time)},
        {"items", Json::Node(items)},
        {"request_id", Json::Node(request_id)}
    });
}


Json::Node GetRouteRequest::ProcessRead(const Database& db) const { 
    const auto route = db.BuildRoute(from, to);

    if(route){
        const auto& [items, total_time] = ProcessRouteItems(route.value());
        return GetRouteRequest::CreateSuccessResponse(request_id, items, total_time);
    }
    
    return CreateNotFoundResponse(request_id);
}


GetMapRequest::GetMapRequest(): ReadRequest(Type::GET_MAP){};
Json::Node GetMapRequest::ProcessRead(const Database& db) const {
    return Json::Node(std::map<std::string,Json::Node>{
        {"map", Json::Node(db.GetMap().RenderToString())},
        {"request_id", Json::Node(request_id)}
    });
}

void GetMapRequest::ParseFromNode(const Json::Node& node){
    request_id = node.AsMap().at("id").AsInt();
}


RequestHolder Request::Create(Request::Type request_type){
    switch (request_type) {
        case Request::Type::ADD_STOP: 
            return std::make_unique<AddStopRequest>();
        case Request::Type::ADD_BUS: 
            return std::make_unique<AddBusRequest>();
        case Request::Type::GET_BUS: 
            return std::make_unique<GetBusRequest>();
        case Request::Type::GET_STOP:
            return std::make_unique<GetStopRequest>();
        case Request::Type::GET_ROUTE:
            return std::make_unique<GetRouteRequest>();
        case Request::Type::GET_MAP:
            return std::make_unique<GetMapRequest>();
        default: 
            return nullptr;
    }
};

std::optional<Request::Type> RequestManager::DetermineOperationType(const Json::Node& node, std::string_view type){
    const auto& request_map = node.AsMap().count("id")>0 ? GET_REQUEST_TYPES : ADD_REQUEST_TYPES;
    if (auto it = request_map.find(type); it != request_map.end()) {
        return it->second;
    }
    return std::nullopt;
}

RequestHolder RequestManager::ParseRequest(const Json::Node &request_node){
    const auto& request_type = DetermineOperationType(request_node, request_node.AsMap().at("type").AsString());
    RequestHolder request = Request::Create(*request_type);
    if(request){
        request->ParseFromNode(request_node);
    }
    return request;
};



Json::Document RequestManager::LoadJson(std::istream& in_stream){
    return Json::Load(in_stream);
}


std::vector<RequestHolder> RequestManager::ReadRequests(std::string_view request_type, Json::Document& doc) {
    const auto& nodes = doc.GetRoot().AsMap().at(std::string(request_type)).AsArray();
    std::vector<RequestHolder> requests;
    requests.reserve(nodes.size());

    for (const auto& node : nodes) {
        if (auto req = ParseRequest(node)) {
            requests.push_back(std::move(req));
        }
    }
    return requests;
}


const Json::Node RequestManager::ProcessRequests(const std::vector<RequestHolder>& requests, Database& db){
    std::vector<Json::Node> responses;

    for (const auto& request_holder: requests){
       auto response = request_holder->Process(db);
       if(response){
        responses.push_back(*response);
       }
    }
    return Json::Node(std::move(responses));
}


void RequestManager::ProcessRoutingSettings(Json::Document& doc , Database& db){
    const auto& routing_settings = doc.GetRoot().AsMap().at("routing_settings");
    db.SetRoutingSettings(routing_settings);
}

void RequestManager::ProcessRenderSettings(Json::Document& doc , Database& db){
    const auto& render_settings = doc.GetRoot().AsMap().at("render_settings");
    db.SetRenderSettings(render_settings);
}