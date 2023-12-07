#include "database.h"

using namespace std;

void Database::Print(ostream& stream) const{
    for (auto& elem: db_vector){
        for(auto& event: elem.second){
            stream << elem.first << " " << event << std::endl;
        }
    }
};

void Database::Add(const Date& date, std::string event){
    if(db_set.count(date) == 0){
        //add to set
        auto insert_it =  db_set[date].insert(event);
        if(insert_it.second){
            //add to vector
            db_vector[date].push_back(event);
        }
    } else{
        std::set<std::string>& events = db_set.at(date);

        auto it = events.find(event);
        if(it == events.end()){
            //insert into set
            db_set[date].insert(event);
            //insert into vector
            db_vector[date].push_back(event);
        }
    }
};



std::string Database::Last(const Date& date) const {
    auto latest_date_it = db_vector.upper_bound(date);

    if( latest_date_it != db_vector.begin()){
        --latest_date_it;
        
        //retrieve date as first element of the map and covnert it to string
        Date latest_date = latest_date_it->first;
        string latest_date_str = latest_date.to_string();

        //retrieve last element of as vector
        std::vector<std::string> latest_events = latest_date_it->second;
        std::string latest_event = latest_events.back();

        return latest_date_str + " " + latest_event;
    } else{
        std::string last_event = "No entries";
        return last_event;
    }

};








