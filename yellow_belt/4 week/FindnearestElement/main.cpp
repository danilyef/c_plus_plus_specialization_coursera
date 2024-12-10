#include <iostream>
#include <algorithm>
#include <set>
#include <utility>
#include <cmath>

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
// set<int>::const_iterator —
// тип итераторов для константного множества целых чисел

int main() {
  set<int> numbers = {1, 4, 6};
  cout <<
      *FindNearestElement(numbers, 0) << " " <<
      *FindNearestElement(numbers, 3) << " " <<
      *FindNearestElement(numbers, 5) << " " <<
      *FindNearestElement(numbers, 6) << " " <<
      *FindNearestElement(numbers, 100) << endl;
      
  set<int> empty_set;
  
  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
  return 0;
}