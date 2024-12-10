#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>

using namespace std;


template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){


  if( distance(range_begin,range_end) < 2){
    return;
  } else{
    vector<typename RandomIt::value_type> v(range_begin, range_end);
    RandomIt mid_it = v.begin() + v.size()/2;

    MergeSort(v.begin(), mid_it);
    MergeSort(mid_it, v.end());

    merge(v.begin(), mid_it, mid_it, v.end(), range_begin);

  }

  

}



 


int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}