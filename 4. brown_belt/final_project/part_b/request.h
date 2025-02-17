#pragma once

#include <string>
#include <iomanip>
#include <cstddef>
#include <string_view>
#include <unordered_map>
#include <memory>
#include <iostream>
#include <optional>
#include <unordered_set>
#include <variant>
#include "database.h"
#include "utils.h"
#include "types.h"


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
    std::unordered_map<std::string, int> neighbors;
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
std::vector<RequestHolder> ReadRequests(std::string_view operation_type,std::istream& in_stream = std::cin);
const std::vector<ResponseType> ProcessRequests(const std::vector<RequestHolder>& requests, Database& db);
void PrintResponses(const std::vector<ResponseType> responses);




