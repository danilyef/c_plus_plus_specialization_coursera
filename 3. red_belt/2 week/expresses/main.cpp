#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>

using namespace std;


set<int>::const_iterator FindNearestElement(
    const set<int>& numbers,
    int border){

    const auto elem = numbers.lower_bound(border);
    if(elem == numbers.begin()){
        return elem; 
    }

    auto prev_elem = std::prev(elem);
    if(elem == numbers.end()){
        return prev_elem;
    }
    //find the closest element to border
    const bool is_left = (border - *prev_elem <= *elem - border);
    return is_left ? prev_elem : elem;
   

    };

class RouteManager {
public:
  void AddRoute(int start, int finish) {
    reachable_lists_[start].insert(finish);
    reachable_lists_[finish].insert(start);
  }
  int FindNearestFinish(int start, int finish) const {
    int result = abs(start - finish);
    if (reachable_lists_.count(start) < 1) {
        return result;
    }
    const set<int>& reachable_stations = reachable_lists_.at(start);
    
    
    
    if (!reachable_stations.empty()) {
      result = min(
          result,
          abs(finish - *FindNearestElement(reachable_stations,finish))
          );
    }
    return result;
  }
private:
  map<int, set<int>> reachable_lists_;
};


int main() {
  RouteManager routes;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int start, finish;
    cin >> start >> finish;
    if (query_type == "ADD") {
      routes.AddRoute(start, finish);
    } else if (query_type == "GO") {
      cout << routes.FindNearestFinish(start, finish) << "\n";
    }
  }

  return 0;
}
