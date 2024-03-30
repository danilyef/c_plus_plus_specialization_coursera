#include "stats.h"
using namespace std;

Stats::Stats() : methods({{"DELETE", 0}, {"GET", 0}, {"POST", 0}, {"PUT", 0}, {"UNKNOWN", 0}}), urls({{"/", 0}, {"/basket", 0}, {"/help", 0}, {"/order", 0}, {"/product", 0}, {"unknown", 0}}){};


void Stats::AddMethod(string_view method){

    if(methods.count(method) == 0){
        methods["UNKNOWN"]++;
    } else{
        methods[method]++;
    }
};


void Stats::AddUri(string_view uri){
    if(urls.count(uri) == 0){
        urls["unknown"]++;
    } else{
        urls[uri]++;
    }
    
};

const map<string_view, int>& Stats::GetMethodStats() const{
    return methods;
};


const map<string_view, int>& Stats::GetUriStats() const{
    return urls;
};


HttpRequest ParseRequest(string_view line){
    HttpRequest http_request;

    line.remove_prefix(line.find_first_not_of(" "));
    http_request.method = line.substr(0,line.find(" "));
    line.remove_prefix(std::min(line.find(" ") + 1, line.size()));

    http_request.uri = line.substr(0,line.find(" "));
    line.remove_prefix(std::min(line.find(" ") + 1, line.size()));

    http_request.protocol = line.substr(0, line.find(" "));
    
    return http_request;
};


