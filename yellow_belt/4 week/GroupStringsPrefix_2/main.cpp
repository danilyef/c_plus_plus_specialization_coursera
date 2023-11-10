/*

Grouping Strings by Prefix: Part 2
Write a more universal version of the FindStartsWith function that takes an arbitrary string consisting of lowercase Latin letters as a prefix.
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
    const string& prefix){
        auto low = std::lower_bound(range_begin,range_end,prefix,[](const string& str,const string& str2 ){return str.substr(0,str2.size()) < str2;});
        auto upper = std::upper_bound(range_begin,range_end,prefix,[](const string& str2,const string& str ){return str2 < str.substr(0,str2.size());});
        std::pair<RandomIt, RandomIt> res = make_pair(low,upper);
        return res;
    };



int main() {
    const std::vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};

    const auto m_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
    for (auto it = m_result.first; it != m_result.second; ++it) {
        std::cout << *it << " ";
    }
    std::cout << endl;

    const auto p_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
    std::cout << (p_result.first - begin(sorted_strings)) << " " <<
        (p_result.second - begin(sorted_strings)) << endl;

    const auto z_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
    std::cout << (z_result.first - begin(sorted_strings)) << " " <<
        (z_result.second - begin(sorted_strings)) << endl;

    return 0;
}