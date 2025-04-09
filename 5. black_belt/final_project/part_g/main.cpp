#include "request.h"
#include "test_runner.h"
#include "database.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include "json.h"
#include <cstdio>



void TestMapRendering() {
    freopen("output.txt", "w", stdout);

    Database db(202);
    std::ifstream file("test_json/input_h_1.json");

    Json::Document doc = RequestManager::LoadJson(file);

    RequestManager::ProcessRoutingSettings(doc, db);
    RequestManager::ProcessRenderSettings(doc, db);
    const auto requests_insert = RequestManager::ReadRequests("base_requests", doc);
    RequestManager::ProcessRequests(requests_insert, db);

    db.UpdateDatabase();
    db.InitializeRouter();
    db.RenderMap();

    const auto requests_get = RequestManager::ReadRequests("stat_requests", doc);
    const Json::Node responses = RequestManager::ProcessRequests(requests_get, db);

    PrintNode(responses, std::cout);

    fclose(stdout);

}

 


int main() {
    //TestMapRendering();
    

    const int vertex_count = 202;
    
    Database db(vertex_count);
    
    Json::Document doc = RequestManager::LoadJson(std::cin);
    
    RequestManager::ProcessRoutingSettings(doc, db);
    RequestManager::ProcessRenderSettings(doc, db);
    const auto requests_insert = RequestManager::ReadRequests("base_requests", doc);
    RequestManager::ProcessRequests(requests_insert, db);

    db.UpdateDatabase();
    db.InitializeRouter();
    db.RenderMap();

    const auto requests_get = RequestManager::ReadRequests("stat_requests", doc);
    const Json::Node responses = RequestManager::ProcessRequests(requests_get, db);
    
    PrintNode(responses, std::cout);

    return 0;
}
