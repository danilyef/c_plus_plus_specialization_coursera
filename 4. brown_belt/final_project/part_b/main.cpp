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
    ss << "Stop Tolstopaltsevo: 55.611087, 37.20829, 3900m to Marushkino\n";
    ss << "Stop Marushkino: 55.595884, 37.209755, 9900m to Rasskazovka\n";
    ss << "Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye\n";
    ss << "Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka\n";
    ss << "Stop Rasskazovka: 55.632761, 37.333324\n";
    ss << "Stop Biryulyovo Zapadnoye: 55.574371, 37.6517, 1800m to Biryusinka, 2400m to Universam, 7500m to Rossoshanskaya ulitsa\n";
    ss << "Stop Biryusinka: 55.581065, 37.64839, 750m to Universam\n";
    ss << "Stop Universam: 55.587655, 37.645687, 900m to Biryulyovo Tovarnaya, 5600m to Rossoshanskaya ulitsa\n";
    ss << "Stop Biryulyovo Tovarnaya: 55.592028, 37.653656, 1300m to Biryulyovo Passazhirskaya\n";
    ss << "Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164, 1200m to Biryulyovo Zapadnoye\n";
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
    const auto requests_insert = ReadRequests("insert");
    ProcessRequests(requests_insert, db);
    db.UpdateBusStats();
    db.UpdateStopStats();

    const auto& requests_get = ReadRequests("get", std::cin);
    const auto responses = ProcessRequests(requests_get, db);

    PrintResponses(std::move(responses));
    return 0;
}
