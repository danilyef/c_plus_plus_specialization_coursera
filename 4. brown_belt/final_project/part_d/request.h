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
#include "types.h"
#include "json.h"


struct Request;
using RequestHolder = std::unique_ptr<Request>;

struct Request {
  enum class Type {
    ADD_STOP,
    ADD_BUS,
    GET_BUS,
    GET_STOP,
    GET_ROUTE
  };
   
    explicit Request(Type type);
    static RequestHolder Create(Type type);
    virtual void ParseFromNode(const Json::Node& node) = 0;
    virtual std::optional<Json::Node> Process(Database& db) = 0;
    virtual ~Request() = default;
    const Type type_;
};

const std::unordered_map<std::string_view, Request::Type> ADD_REQUEST_TYPES = {
    {"Stop", Request::Type::ADD_STOP},
    {"Bus", Request::Type::ADD_BUS}
};

const std::unordered_map<std::string_view, Request::Type> GET_REQUEST_TYPES = {
    {"Bus", Request::Type::GET_BUS},
    {"Stop", Request::Type::GET_STOP},
    {"Route", Request::Type::GET_ROUTE}
};



struct ReadRequest : Request {
    using Request::Request;
    virtual Json::Node ProcessRead(const Database& db) const = 0;
    std::optional<Json::Node> Process(Database& db) override;
    Json::Node CreateNotFoundResponse(int request_id) const;
};

struct ModifyRequest : Request {
    using Request::Request;
    virtual void ProcessModify(Database& db) = 0;
    std::optional<Json::Node> Process(Database& db) override;
};

struct AddStopRequest: ModifyRequest {
    AddStopRequest();
    void ProcessModify(Database& db) override;
    void ParseFromNode(const Json::Node& node) override;
    std::string stop_name; 
    Descriptions::Coordinates coordinates;
    std::unordered_map<std::string, int> neighbors;
};

struct AddBusRequest: ModifyRequest {
    AddBusRequest();
    void ProcessModify(Database& db) override;
    void ParseFromNode(const Json::Node& node) override;
    std::vector<std::string> stops;
    std::string bus_id;
    bool is_roundtrip;
};


struct GetBusRequest: ReadRequest {
    GetBusRequest();
    Json::Node ProcessRead(const Database& db) const override ;
    Json::Node CreateSuccessResponse(int request_id, const Descriptions::BusInformation& busInfo) const;
    void ParseFromNode(const Json::Node& node) override;
    std::string bus_id;
    int request_id;
};


struct GetStopRequest: ReadRequest {
    GetStopRequest();
    Json::Node ProcessRead(const Database& db) const override;
    Json::Node CreateSuccessResponse(int request_id, const Descriptions::StopInformation& stopInfo) const;
    void ParseFromNode(const Json::Node& node) override;
    std::string stop_name;
    int request_id;
};

struct GetRouteRequest: ReadRequest {
    GetRouteRequest();
    Json::Node ProcessRead(const Database& db) const override;
    Json::Node CreateWaitItem(const Descriptions::Wait& wait) const;
    Json::Node CreateStopRouteItem(const Descriptions::StopRoute& route) const;
    Json::Node CreateSuccessResponse(int request_id, Json::Node items, double total_time) const;
    std::pair<Json::Node, double> ProcessRouteItems(const std::vector<Descriptions::RouteInfo>& route) const;
    void ParseFromNode(const Json::Node& node) override;
    std::string from;
    std::string to;
    int request_id;
};


namespace RequestManager{
    std::optional<Request::Type> DetermineOperationType(const Json::Node& node, std::string_view type);
    Json::Document LoadJson(std::istream& in_stream);
    RequestHolder ParseRequest(const Json::Node& request_node);
    std::vector<RequestHolder> ReadRequests(std::string_view request_type, Json::Document& doc);
    const Json::Node ProcessRequests(const std::vector<RequestHolder>& requests, Database& db);
    void ProcessRoutingSettings(Json::Document& doc , Database& db);
}

