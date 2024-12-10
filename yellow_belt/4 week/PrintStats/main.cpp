#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>

using namespace std;

enum class Gender {
  FEMALE,
  MALE
};

struct Person {
  int age;          // age
  Gender gender;    // gender
  bool is_employed; // whether employed
};

// Это пример функции, его не нужно отправлять вместе с функцией PrintStats
template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
    return 0;
  }
  vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
      begin(range_copy), middle, end(range_copy),
      [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
      }
  );
  return middle->age;
}

void PrintStats(vector<Person> persons){

    cout << "Median age = " << ComputeMedianAge(persons.begin(),persons.end()) << endl;

    auto it_f = partition(persons.begin(), persons.end(), []( Person p){
        return p.gender == Gender::FEMALE;
        }
    );
    cout << "Median age for females = " << ComputeMedianAge(persons.begin(),it_f) << endl;

    auto it_m = partition(persons.begin(), persons.end(), []( Person p){
        return p.gender == Gender::MALE;
        }
    );

    cout << "Median age for males = " << ComputeMedianAge(persons.begin(),it_m) << endl;


    auto it_e_f = partition(persons.begin(), persons.end(), []( Person p){
        return (p.gender == Gender::FEMALE & p.is_employed == true);
        }
    );
    cout << "Median age for employed females = " << ComputeMedianAge(persons.begin(),it_e_f) << endl;

    auto it_ue_f = partition(persons.begin(), persons.end(), []( Person p){
        return (p.gender == Gender::FEMALE & p.is_employed == false);
        }
    );
    cout << "Median age for unemployed females = " << ComputeMedianAge(persons.begin(),it_ue_f) << endl;


    auto it_e_m = partition(persons.begin(), persons.end(), []( Person p){
        return (p.gender == Gender::MALE & p.is_employed == true);
        }
    );
    cout << "Median age for employed males = " << ComputeMedianAge(persons.begin(),it_e_m) << endl;

    auto it_ue_m = partition(persons.begin(), persons.end(), []( Person p){
        return (p.gender == Gender::MALE & p.is_employed == false);
        }
    );
    cout << "Median age for unemployed males = " << ComputeMedianAge(persons.begin(),it_ue_m) << endl;
}

int main() {
  vector<Person> persons = {
      {31, Gender::MALE, false},
      {40, Gender::FEMALE, true},
      {24, Gender::MALE, true},
      {20, Gender::FEMALE, true},
      {80, Gender::FEMALE, false},
      {78, Gender::MALE, false},
      {10, Gender::FEMALE, false},
      {55, Gender::MALE, true},
  };
  PrintStats(persons);
  return 0;
}

