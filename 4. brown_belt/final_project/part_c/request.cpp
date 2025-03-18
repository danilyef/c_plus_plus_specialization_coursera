#include "request.h"


Request::Request(Type type): type_(type){};

/*ReadRequest*/
std::optional<Json::Node> ReadRequest::Process(DatabaseStats::Database& db) {
    return ProcessRead(db);
}

/*ModifyRequest*/
std::optional<Json::Node> ModifyRequest::Process(DatabaseStats::Database& db) {
    ProcessModify(db);
    return std::nullopt;
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
    void AddStopRequest::ProcessModify(DatabaseStats::Database& db){
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
void AddBusRequest::ProcessModify(DatabaseStats::Database& db){
    db.AddBus(std::move(bus_id), std::move(stops), is_roundtrip);
}


/*GetBusRequest*/
void GetBusRequest::ParseFromNode(const Json::Node& node){
    bus_id = node.AsMap().at("name").AsString();
    request_id = node.AsMap().at("id").AsInt();
}

GetBusRequest::GetBusRequest(): ReadRequest(Type::GET_BUS){};
Json::Node GetBusRequest::ProcessRead(const DatabaseStats::Database& db) const {
    const auto& bus = db.GetBusInfo(bus_id);
    std::map<std::string,Json::Node> bus_info;
    if(bus){
        try {
            const Descriptions::BusInformation& busInfoObject = bus->get();
            bus_info["route_length"] = Json::Node(busInfoObject.route_len);
            bus_info["request_id"] = Json::Node(request_id);
            bus_info["curvature"] = Json::Node(busInfoObject.curvature);
            bus_info["stop_count"] = Json::Node(busInfoObject.stops);
            bus_info["unique_stop_count"] = Json::Node(busInfoObject.unique_stops);
        } catch (const std::exception& e) {
            std::cerr << "Error processing bus info: " << e.what() << std::endl;
            throw;
        }
    } else {
        bus_info["request_id"] = Json::Node(request_id);
        bus_info["error_message"] = Json::Node(std::string("not found"));
    }
    return Json::Node(std::move(bus_info));
};


/*GetStopRequest*/
void GetStopRequest::ParseFromNode(const Json::Node& node){
    stop_name = node.AsMap().at("name").AsString();
    request_id = node.AsMap().at("id").AsInt();
}

GetStopRequest::GetStopRequest(): ReadRequest(Type::GET_STOP){};
Json::Node GetStopRequest::ProcessRead(const DatabaseStats::Database& db) const {
    const auto& stop = db.GetStopInfo(stop_name);
    std::map<std::string,Json::Node> stop_info;
    if(stop){
        try {
            const Descriptions::StopInformation& stopInfoObject = stop->get();
            std::vector<Json::Node> buses(stopInfoObject.buses.begin(), stopInfoObject.buses.end());
            stop_info["buses"] = Json::Node(buses);
            stop_info["request_id"] = Json::Node(request_id);
        } catch (const std::exception& e) {
            std::cerr << "Error processing stop info: " << e.what() << std::endl;
            throw;
        }
    } else{
        stop_info["request_id"] = Json::Node(request_id);
        stop_info["error_message"] = Json::Node(std::string("not found"));
    }
    return Json::Node(std::move(stop_info));
};



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
        default: 
            return nullptr;
    }
};

std::optional<Request::Type> DetermineOperationType(const Json::Node& node, std::string_view type){
    const auto& request_map = node.AsMap().count("id")>0 ? GET_REQUEST_TYPES : ADD_REQUEST_TYPES;
    if (auto it = request_map.find(type); it != request_map.end()) {
        return it->second;
    }
    return std::nullopt;
}

RequestHolder ParseRequest(const Json::Node &request_node){
    const auto& request_type = DetermineOperationType(request_node, request_node.AsMap().at("type").AsString());
    RequestHolder request = Request::Create(*request_type);
    if(request){
        request->ParseFromNode(request_node);
    }
    return request;
};



Json::Document LoadJson(std::istream& in_stream){
    return Json::Load(in_stream);
}


std::vector<RequestHolder> ReadRequests(std::string_view request_type, Json::Document& doc) {
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


const Json::Node ProcessRequests(const std::vector<RequestHolder>& requests, DatabaseStats::Database& db){
    std::vector<Json::Node> responses;

    for (const auto& request_holder: requests){
       auto response = request_holder->Process(db);
       if(response){
        responses.push_back(*response);
       }
    }
    return Json::Node(std::move(responses));
}

