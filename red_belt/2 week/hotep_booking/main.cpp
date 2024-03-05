#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <deque>
#include <unordered_map>


using namespace std;

class HotelManagement {

public:

  HotelManagement() : current_time(-99999999),hotel_clients(),hotel_by_clients_number(),hotel_rooms_total(),hotel_rooms(), hotel_time(){}

  void Book (int64_t &time, string &hotel_name, int &client_id, int &room_count){
    hotel_time[hotel_name].push_back(time);
    
    hotel_rooms[hotel_name].push_back(room_count);
    hotel_rooms_total[hotel_name] += room_count;
    
    hotel_clients[hotel_name].push_back(client_id);
    hotel_by_clients_number[hotel_name][client_id] += 1;

    current_time = time;
  }

  int Clients(string &hotel_name){  

    if(hotel_by_clients_number[hotel_name].size() == 0){
      return 0;
    }

    Pop_Front(hotel_name);

    return hotel_by_clients_number[hotel_name].size();
  }

  int Rooms(string &hotel_name){

    if(hotel_time[hotel_name].size() == 0){
      return 0;
    }

    Pop_Front(hotel_name);    

    return hotel_rooms_total[hotel_name];
  }

private:

  unordered_map<string,deque<int64_t>> hotel_time;

  unordered_map<string,deque<int>> hotel_rooms;
  unordered_map<string,int> hotel_rooms_total;

  unordered_map<string,deque<int>> hotel_clients;
  unordered_map<string,unordered_map<int,int>> hotel_by_clients_number;

  void Pop_Front(string& hotel_name){
    while(!hotel_time.at(hotel_name).empty() && hotel_time.at(hotel_name).front() <= current_time - 86400){
        hotel_time.at(hotel_name).pop_front();
        
        hotel_rooms_total[hotel_name] -= hotel_rooms.at(hotel_name).front();
        hotel_rooms.at(hotel_name).pop_front();
        
        hotel_by_clients_number.at(hotel_name).at(hotel_clients.at(hotel_name).front()) -= 1;
        if(hotel_by_clients_number.at(hotel_name).at(hotel_clients.at(hotel_name).front()) == 0){
          hotel_by_clients_number.at(hotel_name).erase(hotel_clients.at(hotel_name).front());
        }
        hotel_clients.at(hotel_name).pop_front();            
      }

  }

  int64_t current_time;
};




int main() {

  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  HotelManagement hotel;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;

    if (query_type == "BOOK") {
      int64_t time;
      int client_id, room_count;
      string hotel_name;
      cin >> time >> hotel_name >> client_id >> room_count;
      hotel.Book(time, hotel_name, client_id, room_count);
    } else if (query_type == "CLIENTS") {
      string hotel_name;
      cin >> hotel_name;
      cout << hotel.Clients(hotel_name) << "\n";
    } else if (query_type == "ROOMS") {
      string hotel_name;
      cin >> hotel_name;
      cout << hotel.Rooms(hotel_name) << "\n";
    } 
    
  }
  return 0;
}


