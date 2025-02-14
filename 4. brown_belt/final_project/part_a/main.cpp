#include "request.h"
#include "test_runner.h"
#include "database.h"
#include <fstream>
#include <sstream>
#include <iomanip>


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

