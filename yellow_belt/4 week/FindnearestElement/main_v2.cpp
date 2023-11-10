/*
'Find nearest element'

Write a function called FindNearestElement that, given a set of integers numbers and a specific number border, returns an iterator pointing to the element in the set that is closest to the border. If there are multiple elements that are equally close, return an iterator pointing to the smallest of those elements.

cpp
Copy code
set<int>::const_iterator FindNearestElement(
    const set<int>& numbers,
    int border);
Here, set<int>::const_iterator represents the type of iterators used for a constant set of integers.
*/


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