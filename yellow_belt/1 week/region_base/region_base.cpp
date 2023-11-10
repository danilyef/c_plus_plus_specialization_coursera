/*
You have a database of regions represented by a vector of Region structures:

cpp
Copy code
struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};
Here, Lang is a language identifier:

cpp
Copy code
enum class Lang {
  DE, FR, IT
};
Write a function called FindMaxRepetitionCount that takes the database of regions and determines the maximum number of repetitions (the number of occurrences of the same element) it contains. Two records (objects of type Region) are considered different if they differ in at least one field.

cpp
Copy code
int FindMaxRepetitionCount(const vector<Region>& regions);
If all records are unique, consider the maximum repetition count to be 1. If there are no records, return 0. It is guaranteed that the int type is sufficient to store the answer.

*/


#include <iostream>
#include <vector>
#include <tuple>
#include <map>

using namespace std;

enum class Lang {
  DE, FR, IT
};

struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};

bool operator<(const Region& lhs, const Region& rhs){
    return tie(lhs.std_name,lhs.parent_std_name,lhs.names,lhs.population) < tie(rhs.std_name,rhs.parent_std_name,rhs.names,rhs.population);
}

int FindMaxRepetitionCount(const vector<Region>& regions){

    /*return 0 if vector is empty*/
    if(regions.size() == 0){
        return 0;
    }

    int max_value = 1;
    map<Region,int> dict;


    
    for(Region region: regions){
        ++dict[region];
    }


    for(const auto& pair: dict){
        if(pair.second > max_value){
            max_value = pair.second;
        }
    }
    return max_value;

};

int main() {
  cout << FindMaxRepetitionCount({
      {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      },
  }) << endl;
  
  cout << FindMaxRepetitionCount({
      {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Toulouse",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          31
      },
  }) << endl;

  cout << FindMaxRepetitionCount({}) << endl;
  
  return 0;
}