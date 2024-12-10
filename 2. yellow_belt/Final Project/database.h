#pragma once

#include "date.h"
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>


using namespace std;



class Database {
public:

    void Print(ostream& stream) const;
    void Add(const Date& date, std::string event);
    
    template<typename F>
    int RemoveIf(const F& lambda);
      
    template<typename F>
    std::vector<std::pair<Date,std::string>> FindIf(const F& lambda) const;
    
    std::string Last(const Date& date) const;

private:
    //map<Date,std::pair<std::set<std::string>,std::vector<std::string>>> db;
    map<Date,std::set<std::string>> db_set;
    map<Date,std::vector<std::string>> db_vector;
};



template<typename F>
    int Database::RemoveIf(const F& lambda){
        int deleted_elements = 0;

        for(auto it = db_vector.begin(); it != db_vector.end();){
            auto& date = it->first;
            auto& events = it->second;
            
            auto to_remove = std::stable_partition(events.begin(), events.end(), [&date, &lambda](const auto& event){ 
                return !lambda(date,event);
            });
            
            deleted_elements += std::distance(to_remove,events.end());

            //delete from set:
            for(auto it_event = to_remove;it_event != events.end();++it_event){
                db_set[date].erase(*it_event);
            }

            //delete from vector:
            events.erase(to_remove,events.end());

            if(events.size() == 0){
                db_vector.erase(it++);
                db_set.erase(date);
            } else{
                ++it;
            }
        }
    return deleted_elements;
};





template<typename F>
std::vector<std::pair<Date,std::string>> Database::FindIf(const F& lambda) const{
    std::vector<std::pair<Date,std::string>> found_elements;
    for(auto &item : db_vector){
        auto& date = item.first;
        auto& events = item.second;

        auto check_event = [&date, &lambda](const auto& event){
            return lambda(date,event);
        };
        
        for (auto it = std::find_if(events.begin(), events.end(), check_event);
            it != events.end();
            it = std::find_if(++it, events.end(), check_event)){
                found_elements.push_back(std::make_pair(date,*it));
            }
            

        }


    return found_elements;
};

