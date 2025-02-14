#include "request.h"


Request::Request(Type type): type_(type){};

AddStopRequest::AddStopRequest(): ModifyRequest(Type::ADD_STOP){};
void AddStopRequest::Process(Database& db){
    db.AddStop(std::move(stop_name), std::move(coordinates));
}

void AddStopRequest::ParseFromString(std::string_view input){
    stop_name = std::string(ReadToken(input, ": "));
    coordinates.latitude = ConvertToDouble(ReadToken(input, ", "));
    coordinates.longitude = ConvertToDouble(ReadToken(input, "\n"));
}



AddBusRequest::AddBusRequest(): ModifyRequest(Type::ADD_BUS){};
void AddBusRequest::Process(Database& db){
    db.AddBus(std::move(bus_id), std::move(stops), is_backandforth);
}


void AddBusRequest::ParseFromString(std::string_view input){
    bus_id = std::string(ReadToken(input, ": "));
    char delimiter = getDelimiter(input);
    is_backandforth = delimiter == '-';
    while (!input.empty()){
        if(delimiter == '-'){
            stops.emplace_back(ReadToken(input, " - "));
        } else if(delimiter == '>'){
            stops.emplace_back(ReadToken(input, " > "));
        } else {
            stops.emplace_back(ReadToken(input, "\n"));
        }
    }
}


GetBusRequest::GetBusRequest(): ReadRequest(Type::GET_BUS){};
std::pair<std::string, BusInformation> GetBusRequest::Process(const Database& db) const {
    const auto& bus = db.GetBusInfo(bus_id);
    if(bus){
        return std::make_pair(std::move(bus_id), *bus);
    } else {
        return std::make_pair(std::move(bus_id), BusInformation());
    }
};

void GetBusRequest::ParseFromString(std::string_view input){
    bus_id = ReadToken(input, "\n");
}


GetStopRequest::GetStopRequest(): ReadRequest(Type::GET_STOP){};
std::pair<std::string, StopInformation> GetStopRequest::Process(const Database& db) const {
    const auto& stop = db.GetStopInfo(stop_name);
    if(stop){
        return std::make_pair(std::move(stop_name), *stop);
    } else {
        return std::make_pair(std::move(stop_name), StopInformation());
    }
};

void GetStopRequest::ParseFromString(std::string_view input){
    stop_name = ReadToken(input, "\n");
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
        default: 
            return nullptr;
    }
};

std::optional<Request::Type> ConvertRequestTypeFromString(std::string_view operation_type, std::string_view type_str) {
  if (operation_type == "insert") {
    if (const auto it = STR_TO_REQUEST_ADD_TYPE.find(type_str); it != STR_TO_REQUEST_ADD_TYPE.end()) {
      return it->second;
    }
  } else if (operation_type == "get") {
    if (const auto it = STR_TO_REQUEST_GET_TYPE.find(type_str); it != STR_TO_REQUEST_GET_TYPE.end()) {
      return it->second;
    }
  }
  return std::nullopt;
};


RequestHolder ParseRequest(std::string_view operation_type,std::string_view request_str){
    const auto request_type = ConvertRequestTypeFromString(operation_type, ReadToken(request_str));
    if (!request_type) {
        return nullptr;
    }
    RequestHolder request = Request::Create(*request_type);
    if(request){
        request->ParseFromString(request_str);
    }
    
    return request;
};


std::vector<RequestHolder> ReadRequests(std::string_view operation_type, std::istream& in_stream = std::cin) {
    size_t request_count;
    in_stream >> request_count;
    in_stream.ignore();

    std::vector<RequestHolder> requests;
    requests.reserve(request_count);

    for(size_t i = 0; i < request_count; ++i) { 
        std::string request_str;
        std::getline(in_stream, request_str);
        
        if (auto request = ParseRequest(operation_type, request_str)) {
            requests.push_back(std::move(request));
        }
    }
    return requests;
}




std::vector<ResponseType> ProcessRequests(const std::vector<RequestHolder>& requests, Database& db){
    std::vector<ResponseType> responses;

    for (const auto& request_holder: requests){
        if(request_holder->type_ == Request::Type::ADD_BUS){
            auto& request = static_cast<AddBusRequest&>(*request_holder);
            request.Process(db);

        } else if(request_holder->type_ == Request::Type::ADD_STOP){
            auto& request = static_cast<AddStopRequest&>(*request_holder);
            request.Process(db);

        } else if(request_holder->type_ == Request::Type::GET_BUS){
            const auto& request = static_cast<const GetBusRequest&>(*request_holder);
            responses.push_back(request.Process(db));

        } else if(request_holder->type_ == Request::Type::GET_STOP){
            const auto& request = static_cast<const GetStopRequest&>(*request_holder);
            responses.push_back(request.Process(db));

        } else {
            std::cout << "Error" << std::endl;
        }
    }
    return responses;
}


std::ostream& operator<<(std::ostream& os, const BusInformation& bus_info){
    if(bus_info.found){
        os << bus_info.stops << " stops on route, " << bus_info.unique_stops << " unique stops, " << bus_info.route_len << " route length";
    } else {
        os << "not found";
    }
    return os;
}



std::ostream& operator<<(std::ostream& os, const StopInformation& stop_info){
    if(!stop_info.found){
        os << "not found";
    } else {
        if(stop_info.buses.empty()){
            os << "no buses";
        } else {
            os << "buses ";
            for(const auto& bus: stop_info.buses){
                os << bus << " ";
            }
        }
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const ResponseType& response) {
    if (std::holds_alternative<BusInformation>(response.second)) {
        os << "Bus " << response.first << ": ";
    } else if (std::holds_alternative<StopInformation>(response.second)) {
        os << "Stop " << response.first << ": ";
    }
    std::visit([&os](const auto& value) { os << value; }, response.second);
    return os;
}






void PrintResponses(const std::vector<ResponseType>& responses){
    std::cout << std::fixed << std::setprecision(6);
    for(const auto& response: responses){
        std::cout << response << std::endl;
    }
}
