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
    RandomIt it1 = v.begin() + v.size()/3;
    RandomIt it2 = v.begin() + 2 * v.size()/3;

    MergeSort(v.begin(), it1);
    MergeSort(it1, it2);
    MergeSort(it2, v.end());

    vector<typename RandomIt::value_type> temp;
    merge(v.begin(), it1, it1, it2, back_inserter(temp));
    merge(temp.begin(), temp.end(), it2, v.end(), range_begin);

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