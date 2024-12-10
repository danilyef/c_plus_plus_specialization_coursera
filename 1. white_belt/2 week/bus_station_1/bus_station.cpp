#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;



int main(){
    /*
    Q - number of operations
    operation - whih operation to perform
    country_new - new country for rename
    country_old - old country to rename
    country - country to get information about
    capital - capital of the country
    */
    int Q;
    string operation;
    map<string,vector<string> > bus_route; 
    vector<string> bus;

    cin >> Q;
    for(int i = 0;i< Q;i++){
        cin >> operation;
        if(operation == "NEW_BUS"){
            string bus_name;
            int num_stops;
            cin >> bus_name >> num_stops;
            bus.push_back(bus_name);
            bus_route[bus_name] = {};
            for(int i = 0; i< num_stops; i++){
                string stop_name;
                cin >> stop_name;
                bus_route[bus_name].push_back(stop_name);
            }

        } else if(operation == "BUSES_FOR_STOP"){
            string stop_name;
            cin >> stop_name;
            
            for(const auto& b: bus){
                for(const auto& stop:bus_route[b]){
                    if(stop_name == stop){
                        cout << b << " ";
                        count +=1;
                    }
                }
            }

            cout << endl;
            

        } else if(operation == "STOPS_FOR_BUS"){
            string bus_name;
            cin >> bus_name;
            if(bus_route.count(bus_name) == 0){
                cout << "No bus" << endl;
            } else{
                for(const auto& stop: bus_route[bus_name]){
                int count = 0;
                cout << "Stop " << stop << ": ";
                for(const auto& b: bus){
                    if(b == bus_name){
                        continue;
                    }
                    for(const auto& s:bus_route[b]){
                        if(stop == s){
                            cout << b << " ";
                            count +=1;
                            break;
                        }
                    }
                }
                if(count == 0){
                    cout << "no interchange";
                }
                cout << endl;
                }
            }
        } else if(operation == "ALL_BUSES"){
            if(bus_route.size() == 0){
                cout << "No buses" << endl;
            } else{
                for(const auto& item: bus_route){
                    if(item.second.size() == 0){
                        
                    }
                    cout << "Bus " << item.first << ": ";
                    for(const auto& stop:item.second){
                        cout << stop << " ";
                    }         
                    cout << endl;
                }

            } 
        }    
    }
    return 0;
}