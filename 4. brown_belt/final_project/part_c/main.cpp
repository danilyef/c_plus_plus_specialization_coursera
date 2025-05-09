#include "request.h"
#include "test_runner.h"
#include "database.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include "json.h"


void TestBasicRouteProcessing() {
    DatabaseStats::Database db;
    std::stringstream ss;
    ss << R"({
        "base_requests": [
            {
                "type": "Stop",
                "name": "Tolstopaltsevo",
                "latitude": 55.611087,
                "longitude": 37.20829,
                "road_distances": {
                    "Marushkino": 3900
                }
            },
            {
                "type": "Stop", 
                "name": "Marushkino",
                "latitude": 55.595884,
                "longitude": 37.209755,
                "road_distances": {
                    "Rasskazovka": -9900
                }
            },
            {
                "type": "Bus",
                "name": "256",
                "stops": [
                    "Biryulyovo Zapadnoye",
                    "Biryusinka",
                    "Universam",
                    "Biryulyovo Tovarnaya", 
                    "Biryulyovo Passazhirskaya",
                    "Biryulyovo Zapadnoye"
                ],
                "is_roundtrip": true
            },
            {
                "type": "Bus",
                "name": "750",
                "stops": [
                    "Tolstopaltsevo",
                    "Marushkino",
                    "Rasskazovka"
                ],
                "is_roundtrip": false
            },
            {
                "type": "Stop",
                "name": "Rasskazovka",
                "latitude": 55.632761,
                "longitude": 37.333324,
                "road_distances": {}
            },
            {
                "type": "Stop",
                "name": "Biryulyovo Zapadnoye",
                "latitude": 55.574371,
                "longitude": 37.6517,
                "road_distances": {
                    "Biryusinka": 1800,
                    "Universam": 2400,
                    "Rossoshanskaya ulitsa": 7500
                }
            },
            {
                "type": "Stop",
                "name": "Biryusinka",
                "latitude": 55.581065,
                "longitude": 37.64839,
                "road_distances": {
                    "Universam": 750
                }
            },
            {
                "type": "Stop",
                "name": "Universam",
                "latitude": 55.587655,
                "longitude": 37.645687,
                "road_distances": {
                    "Biryulyovo Tovarnaya": 900,
                    "Rossoshanskaya ulitsa": 5600
                }
            },
            {
                "type": "Stop",
                "name": "Biryulyovo Tovarnaya",
                "latitude": 55.592028,
                "longitude": 37.653656,
                "road_distances": {
                    "Biryulyovo Passazhirskaya": 1300
                }
            },
            {
                "type": "Stop",
                "name": "Biryulyovo Passazhirskaya",
                "latitude": 55.580999,
                "longitude": 37.659164,
                "road_distances": {
                    "Biryulyovo Zapadnoye": 1200
                }
            },
            {
                "type": "Bus",
                "name": "828",
                "stops": [
                    "Biryulyovo Zapadnoye",
                    "Universam",
                    "Rossoshanskaya ulitsa",
                    "Biryulyovo Zapadnoye"
                ],
                "is_roundtrip": true
            },
            {
                "type": "Stop",
                "name": "Rossoshanskaya ulitsa",
                "latitude": 55.595579,
                "longitude": -37.605757,
                "road_distances": {}
            },
            {
                "type": "Stop",
                "name": "Prazhskaya",
                "latitude": 55.611678,
                "longitude": 37.603831,
                "road_distances": {}
            }
        ],
        "stat_requests": [
            {
                "id": 356136519,
                "type": "Bus",
                "name": "256"
            },
            {
                "id": 1676384590,
                "type": "Bus",
                "name": "-750"
            },
            {
                "id": 737984746,
                "type": "Bus",
                "name": "751"
            },
            {
                "id": 1880997796,
                "type": "Stop",
                "name": "Samara"
            },
            {
                "id": -413248915,
                "type": "Stop",
                "name": "Prazhskaya"
            },
            {
                "id": 1800657631,
                "type": "Stop",
                "name": "Biryulyovo Zapadnoye"
            }
        ]
    })";

    Json::Document doc = LoadJson(ss);
    const auto requests_insert = ReadRequests("base_requests", doc);
    ProcessRequests(requests_insert, db);

    db.UpdateStats();

    const auto requests_get = ReadRequests("stat_requests", doc);
    const Json::Node responses = ProcessRequests(requests_get, db);
    
    PrintNode(responses, std::cout);
}



int main() {
    //TestBasicRouteProcessing();
    
    DatabaseStats::Database db;
    
    Json::Document doc = LoadJson(std::cin);
    const auto requests_insert = ReadRequests("base_requests", doc);
    ProcessRequests(requests_insert, db);
    
    db.UpdateStats(); 
    
    const auto requests_get = ReadRequests("stat_requests", doc);
    const Json::Node responses = ProcessRequests(requests_get, db);
    
    PrintNode(responses, std::cout);
    
    return 0;
}
