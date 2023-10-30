/*
Grouping Strings by Prefix: Part 1. Grouping by Character
Write a function called FindStartsWith:

It takes a sorted set of strings represented by iterators range_begin and range_end and a single character prefix.
It returns a range of strings that start with the character prefix as a pair of iterators.

If the resulting range is empty, its boundaries should point to the position in the container where you can insert any string that starts with the character prefix without violating the sorting order (similar to the equal_range algorithm). It is guaranteed that the strings consist only of lowercase Latin letters, and the prefix character is also a lowercase Latin letter.

The search should be carried out with logarithmic complexity, for example, using binary search.


*/


#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <utility>

using namespace std;


template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    char prefix){
        auto low = std::lower_bound(range_begin,range_end,prefix,[](const string& str,char c ){return str[0] < c;});
        auto upper = std::upper_bound(range_begin,range_end,prefix,[](char c,const string& str ){return c < str[0];});
        std::pair<RandomIt, RandomIt> res = make_pair(low,upper);
        return res;
    };



int main() {
    const std::vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};

    const auto m_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
    for (auto it = m_result.first; it != m_result.second; ++it) {
        std::cout << *it << " ";
    }
    std::cout << endl;

    const auto p_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
    std::cout << (p_result.first - begin(sorted_strings)) << " " <<
        (p_result.second - begin(sorted_strings)) << endl;

    const auto z_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
    std::cout << (z_result.first - begin(sorted_strings)) << " " <<
        (z_result.second - begin(sorted_strings)) << endl;

    return 0;
}