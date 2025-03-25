#include "request.h"
#include "test_runner.h"
#include "database.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include "json.h"


#include <cstdio>



void TestBasicRouteProcessing() {
   freopen("output.txt", "w", stdout);

    DatabaseStats::Database db(202);
    std::ifstream file("input_test.json");

    Json::Document doc = LoadJson(file);

    ProcessRoutingSettings(doc, db);
    const auto requests_insert = ReadRequests("base_requests", doc);
    ProcessRequests(requests_insert, db);

    db.UpdateDatabase();
    db.InitializeRouter();

    const auto requests_get = ReadRequests("stat_requests", doc);
    const Json::Node responses = ProcessRequests(requests_get, db);

    PrintNode(responses, std::cout);

    fclose(stdout);

}




int main() {
    //TestBasicRouteProcessing();
    const int vertex_count = 202;
    
    DatabaseStats::Database db(vertex_count);
    
    Json::Document doc = LoadJson(std::cin);
    
    ProcessRoutingSettings(doc, db);
    const auto requests_insert = ReadRequests("base_requests", doc);
    ProcessRequests(requests_insert, db);

    db.UpdateDatabase();
    db.InitializeRouter();

    const auto requests_get = ReadRequests("stat_requests", doc);
    const Json::Node responses = ProcessRequests(requests_get, db);
    
    PrintNode(responses, std::cout);
    
    
    return 0;
}
