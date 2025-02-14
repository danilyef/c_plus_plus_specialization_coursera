#include <cmath>
#include <cstddef>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <system_error>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

using namespace std;



struct Coordinates {
    double latitude;
    double longitude;
};

struct BusInformation{
    BusInformation() : bus_stops(), stops(0), unique_stops(0), route_len(0), found(false), is_backandforth(false) {};
    BusInformation(std::vector<std::string> bus_stops,bool is_backandforth) : bus_stops(std::move(bus_stops)), stops(0), unique_stops(0), route_len(0), found(false), is_backandforth(is_backandforth) {};
    std::vector<std::string> bus_stops;
    size_t stops;
    size_t unique_stops;
    double route_len;
    bool is_backandforth;
    bool found;
};


struct StopInformation{
    StopInformation() : buses(), coordinates(), found(false) {};
    StopInformation(Coordinates coordinates) : buses(), coordinates(std::move(coordinates)), found(true) {};
    std::set<std::string> buses;
    Coordinates coordinates;
    bool found;
};


inline bool operator==(const BusInformation& lhs, const BusInformation& rhs) {
    return lhs.bus_stops == rhs.bus_stops && lhs.stops == rhs.stops && lhs.unique_stops == rhs.unique_stops && lhs.route_len == rhs.route_len;
}







enum class InvalidRequestReason {
    BUS_NOT_FOUND
};


std::pair<std::string_view, std::optional<std::string_view>> SplitTwoStrict(std::string_view s, std::string_view delimiter = " ");

std::pair<std::string_view, std::string_view> SplitTwo(std::string_view s, std::string_view delimiter = " ");

std::string_view ReadToken(std::string_view& s, std::string_view delimiter = " ");

int ConvertToInt(std::string_view str);
double ConvertToDouble(std::string_view str);


constexpr char getDelimiter(std::string_view sv) { 
    size_t pos1 = sv.find('-');
    size_t pos2 = sv.find('>');

    if (pos1 != std::string_view::npos) return '-';
    else if (pos2 != std::string_view::npos) return '>';
    else return '\0';
}

const double DEG_TO_RAD = 3.1415926535 / 180.0;

double ComputeDistance(const Coordinates& lhs, const Coordinates& rhs);




namespace Stats {
    size_t CalculateUniqueStops(const std::vector<std::string>& stops);
    size_t CalculateTotalStops(const std::vector<std::string>& stops);
    double CalculateTotalLength(const std::unordered_map<std::string, Coordinates>& stops, const std::vector<std::string>& bus_route); 
};

class Database {


public:

    /*Getters*/
    std::optional<std::reference_wrapper<const BusInformation>> GetBusInfo(const std::string& bus_id) const;
    std::optional<std::reference_wrapper<const StopInformation>> GetStopInfo(const std::string& stop_name) const;
    
    /*Setters*/
    void AddBus(std::string bus_id, std::vector<std::string> stops,bool is_backandforth);
    void AddStop(std::string stop_name, Coordinates coordinates);

    /*Stats*/
    void UpdateBusStats();
    void UpdateStopStats();


private:
    std::unordered_map<std::string,BusInformation> bus_db;
    std::unordered_map<std::string,StopInformation> stop_db;
    
};





struct Request;
using RequestHolder = std::unique_ptr<Request>;

struct Request {
  enum class Type {
    ADD_STOP,
    ADD_BUS,
    GET_BUS,
    GET_STOP
  };
   
    explicit Request(Type type);
    static RequestHolder Create(Type type);
    virtual void ParseFromString(std::string_view input) = 0;
    virtual ~Request() = default;
    const Type type_;
};

const std::unordered_map<std::string_view, Request::Type> STR_TO_REQUEST_ADD_TYPE = {
    {"Stop", Request::Type::ADD_STOP},
    {"Bus", Request::Type::ADD_BUS}
};

const std::unordered_map<std::string_view, Request::Type> STR_TO_REQUEST_GET_TYPE = {
    {"Bus", Request::Type::GET_BUS},
    {"Stop", Request::Type::GET_STOP}
};



template <typename ResultType>
struct ReadRequest : Request {
    using Request::Request;
    virtual std::pair<std::string, ResultType> Process(const Database& db) const = 0;
};

struct ModifyRequest : Request {
    using Request::Request;
    virtual void Process(Database& db) = 0;
};

struct AddStopRequest: ModifyRequest {
    AddStopRequest();
    void Process(Database& db) override;
    void ParseFromString(std::string_view input) override;
    std::string stop_name; 
    Coordinates coordinates;
};

struct AddBusRequest: ModifyRequest {
    AddBusRequest();
    void Process(Database& db) override;
    void ParseFromString(std::string_view input) override;
    std::vector<std::string> stops;
    std::string bus_id;
    bool is_backandforth;
};


struct GetBusRequest: ReadRequest<BusInformation> {
    GetBusRequest();
    std::pair<std::string, BusInformation> Process(const Database& db) const override ;
    void ParseFromString(std::string_view input) override;
    std::string bus_id;
};


struct GetStopRequest: ReadRequest<StopInformation> {
    GetStopRequest();
    std::pair<std::string, StopInformation> Process(const Database& db) const override;
    void ParseFromString(std::string_view input) override;
    std::string stop_name;
};


using ResponseType = std::pair<std::string, std::variant<BusInformation, StopInformation>>;

std::ostream& operator<<(std::ostream& os, const BusInformation& bus_info);
std::ostream& operator<<(std::ostream& os, const StopInformation& stop_info);
std::ostream& operator<<(std::ostream& os, const ResponseType& response);


/* Request related functions */
std::optional<Request::Type> ConvertRequestTypeFromString(std::string_view operation_type, std::string_view type_str);
RequestHolder ParseRequest(std::string_view operation_type,std::string_view request_str);
std::vector<RequestHolder> ReadRequests(std::string_view operation_type,std::istream& in_stream);
std::vector<ResponseType> ProcessRequests(const std::vector<RequestHolder>& requests, Database& db);
void PrintResponses(const std::vector<ResponseType>& responses);





std::pair<std::string_view, std::optional<std::string_view>> SplitTwoStrict(std::string_view s, std::string_view delimiter) {
  const size_t pos = s.find(delimiter);
  if (pos == s.npos) {
    return {s, std::nullopt};
  } else {
    return {s.substr(0, pos), s.substr(pos + delimiter.length())};
  }
}

std::pair<std::string_view, std::string_view> SplitTwo(std::string_view s, std::string_view delimiter) {
  const auto [lhs, rhs_opt] = SplitTwoStrict(s, delimiter);
  return {lhs, rhs_opt.value_or("")};
}

std::string_view ReadToken(std::string_view& s, std::string_view delimiter) {
  const auto [lhs, rhs] = SplitTwo(s, delimiter);
  s = rhs;
  return lhs;
}


int ConvertToInt(std::string_view str) {
  size_t pos;
  const int result = std::stoi(std::string(str), &pos);
  if (pos != str.length()) {
    std::stringstream error;
    error << "string " << str << " contains " << (str.length() - pos) << " trailing chars";
    throw std::invalid_argument(error.str());
  }
  return result;
}


/*
TO use in the newer compilers from C++17

int ConvertToInt(std::string_view str) {
  int value;
  auto result = std::from_chars(str.data(), str.data() + str.size(), value);
  if (result.ec != std::errc()) {
    throw std::invalid_argument("Invalid integer format");
  }
  return value;
}
*/


double ConvertToDouble(std::string_view str) {
  size_t pos;
  const double result = std::stod(std::string(str), &pos);
  if (pos != str.length()) {
    std::stringstream error;
    error << "string " << str << " contains " << (str.length() - pos) << " trailing chars";
    throw std::invalid_argument(error.str());
  }
  return result;
}


/*
TO use in the newer compilers from C++17

double ConvertToDouble(std::string_view str) {

  double value;
  auto result = std::from_chars(str.data(), str.data() + str.size(), value);
  if (result.ec != std::errc()) {
    throw std::invalid_argument("Invalid double format");
  }
  return value; 
}
*/

double ComputeDistance(const Coordinates& lhs, const Coordinates& rhs) {
    // Переводим широту и долготу в радианы
    double lat1_rad = lhs.latitude * DEG_TO_RAD;
    double lon1_rad = lhs.longitude * DEG_TO_RAD;
    double lat2_rad = rhs.latitude * DEG_TO_RAD;
    double lon2_rad = rhs.longitude * DEG_TO_RAD;

    // Вычисляем расстояние по формуле
    double delta_lon = std::abs(lon1_rad - lon2_rad);
    double distance = std::acos(std::sin(lat1_rad) * std::sin(lat2_rad) +
                                std::cos(lat1_rad) * std::cos(lat2_rad) *
                                std::cos(delta_lon)) * 6371000;  // 6371000 — радиус Земли в метрах

    return distance;
}
namespace Stats {
size_t CalculateUniqueStops(const std::vector<std::string>& stops){
    std::unordered_set<std::string_view> unique_stops;
    unique_stops.reserve(stops.size());
    for(const auto& stop_name : stops){
        unique_stops.emplace(stop_name);
    }
    return unique_stops.size();
}


size_t CalculateTotalStops(const std::vector<std::string>& stops){
    return stops.size();
}

double CalculateTotalLength(const std::unordered_map<std::string, StopInformation>& stops, const std::vector<std::string>& bus_route){

    double total_length = 0;

    /*Cached coordinates*/
    std::vector<const Coordinates*> cached_coordinates;
    cached_coordinates.reserve(bus_route.size());

    for (const auto& stop_name : bus_route){
        cached_coordinates.push_back(&stops.at(stop_name).coordinates);
    }

    /*Calculate total length*/
    for(size_t i = 0; i < bus_route.size() - 1; ++i){
        total_length += ComputeDistance(*cached_coordinates[i], 
                                        *cached_coordinates[i + 1]);
    }
    return total_length;
}

}

/*Database Bus*/
void Database::AddBus(std::string bus_id, std::vector<std::string> stops,bool is_backandforth){
    bus_db.emplace(std::move(bus_id), BusInformation(std::move(stops),is_backandforth));
};



std::optional<std::reference_wrapper<const BusInformation>> Database::GetBusInfo(const std::string& bus_id) const {
    auto it = bus_db.find(bus_id);
    if (it != bus_db.end()) {
        return it->second;
    }
    return std::nullopt;
};



/*Database Stop*/
void Database::AddStop(std::string stop_name, Coordinates coordinates){
    stop_db.emplace(std::move(stop_name), StopInformation(coordinates));
};


std::optional<std::reference_wrapper<const StopInformation>> Database::GetStopInfo(const std::string& stop_name) const{
    auto it = stop_db.find(stop_name);
    if (it != stop_db.end()) {
        return it->second;
    }
    return std::nullopt;
};


/* Updates Stats */
void Database::UpdateBusStats(){

    for(auto& [bus_id, bus_info] : bus_db){

        const auto& stops_list = bus_info.bus_stops;

        /*Total stops*/ 
        const size_t total_stops = bus_info.is_backandforth ? Stats::CalculateTotalStops(stops_list) * 2 - 1 : Stats::CalculateTotalStops(stops_list);
        /*Unique stops*/
        const size_t unique_stops_count = Stats::CalculateUniqueStops(stops_list);

        /*Total length*/

        double total_length = Stats::CalculateTotalLength(stop_db, stops_list);
        if(bus_info.is_backandforth){
            total_length *= 2.0;
        }
        
        /* Update */

        bus_info.stops = total_stops;
        bus_info.unique_stops = unique_stops_count;
        bus_info.route_len = total_length;
        bus_info.is_backandforth = true;
        bus_info.found = true;

    }
};

void Database::UpdateStopStats(){
    for(auto& [bus_id, bus_info] : bus_db){
        for(const auto& stop_name : bus_info.bus_stops){
            auto it = stop_db.find(stop_name);
            if(it != stop_db.end()){
                it->second.buses.insert(bus_id);
            }
        }
    }
};







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


void TestBasicRouteProcessing() {
    Database db;
    std::stringstream ss;
    ss << "13\n";
    ss << "Stop Tolstopaltsevo: 55.611087, 37.20829\n";
    ss << "Stop Marushkino: 55.595884, 37.209755\n";
    ss << "Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye\n";
    ss << "Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka\n";
    ss << "Stop Rasskazovka: 55.632761, 37.333324\n";
    ss << "Stop Biryulyovo Zapadnoye: 55.574371, 37.6517\n";
    ss << "Stop Biryusinka: 55.581065, 37.64839\n";
    ss << "Stop Universam: 55.587655, 37.645687\n";
    ss << "Stop Biryulyovo Tovarnaya: 55.592028, 37.653656\n";
    ss << "Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164\n";
    ss << "Bus 828: Biryulyovo Zapadnoye > Universam > Rossoshanskaya ulitsa > Biryulyovo Zapadnoye\n";
    ss << "Stop Rossoshanskaya ulitsa: 55.595579, 37.605757\n";
    ss << "Stop Prazhskaya: 55.611678, 37.603831\n";
    ss << "6\n";
    ss << "Bus 256\n";
    ss << "Bus 750\n";
    ss << "Bus 751\n";
    ss << "Stop Samara\n";
    ss << "Stop Prazhskaya\n";
    ss << "Stop Biryulyovo Zapadnoye\n";

    const auto requests_insert = ReadRequests("insert", ss);
    ProcessRequests(requests_insert, db);
    db.UpdateBusStats();
    db.UpdateStopStats();

    const auto requests_get = ReadRequests("get", ss);
    auto responses = ProcessRequests(requests_get, db);
    
    //ASSERT_EQUAL(responses.size(), 3u);
    //ASSERT_EQUAL(responses[0], "Bus 256: 6 stops on route, 5 unique stops, 4371.02 route length");
    //ASSERT_EQUAL(responses[1], "Bus 750: 5 stops on route, 3 unique stops, 20939.5 route length");
    //ASSERT_EQUAL(responses[2], "Bus 751: not found");
    for(const auto& response: responses){
        std::cout << response << std::endl;
    }
}

/*
int main() {
    TestBasicRouteProcessing();
    return 0;
}
*/



int main() {
    Database db;
    const auto requests_insert = ReadRequests("insert", std::cin);
    ProcessRequests(requests_insert, db);
    db.UpdateBusStats();
    db.UpdateStopStats();

    const auto requests_get = ReadRequests("get", std::cin);
    auto responses = ProcessRequests(requests_get, db);

    PrintResponses(responses);
    return 0;
}

