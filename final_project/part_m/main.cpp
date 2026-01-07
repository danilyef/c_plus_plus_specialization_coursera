#include "request.h"
#include "test_runner.h"
#include "database.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include "json.h"
#include <cstdio>

int main() {
    const int vertex_count = 202;
    
    Database db(vertex_count);
    
    Json::Document doc = RequestManager::LoadJson(std::cin);
    
    RequestManager::ProcessRoutingSettings(doc, db);
    RequestManager::ProcessRenderSettings(doc, db);
    RequestManager::ProcessRequests(RequestManager::ReadRequests("base_requests", doc), db);

    db.UpdateDatabase();
    db.InitializeRouter();
    db.RenderMap();
    db.GetMap().SaveToFile("output_map.svg"); 

    const Json::Node responses = RequestManager::ProcessRequests(RequestManager::ReadRequests("stat_requests", doc), db);
    
    PrintNode(responses, std::cout);

    return 0;
}
