#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <utility>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){


  if(distance(range_begin,range_end) < 2){
    return;
  } else{
    vector<typename RandomIt::value_type> v(make_move_iterator(range_begin), make_move_iterator(range_end));
    auto it1 = v.begin() + v.size()/3;
    auto it2 = v.begin() + 2 * v.size()/3;

    MergeSort(v.begin(), it1);
    MergeSort(it1, it2);
    MergeSort(it2, v.end());

    vector<typename RandomIt::value_type> temp;
    merge(make_move_iterator(v.begin()), make_move_iterator(it1), make_move_iterator(it1), make_move_iterator(it2), back_inserter(temp));
    merge(make_move_iterator(temp.begin()), make_move_iterator(temp.end()), make_move_iterator(it2), make_move_iterator(v.end()), range_begin);

  } 

}

/*
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){


  if(distance(range_begin,range_end) < 2){
    return;
  } else{
    vector<typename RandomIt::value_type> v(range_begin, range_end);
    auto it1 = v.begin() + v.size()/3;
    auto it2 = v.begin() + 2 * v.size()/3;

    MergeSort(v.begin(), it1);
    MergeSort(it1, it2);
    MergeSort(it2, v.end());

    vector<typename RandomIt::value_type> temp;
    merge(v.begin(), it1, it1, it2, back_inserter(temp));
    merge(temp.begin(), temp.end(), it2, v.end(), range_begin);

  }

}
*/

void TestIntVector() {
    vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}
