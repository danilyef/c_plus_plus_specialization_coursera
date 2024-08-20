#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <utility>
#include <tuple>

using namespace std;


template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
    : first(begin)
    , last(end)
  {
  }

  Iterator begin() const {
    return first;
  }

  Iterator end() const {
    return last;
  }

private:
  Iterator first, last;
};

template <typename Collection>
auto Head(Collection& v, size_t top) {
  return IteratorRange{v.begin(), next(v.begin(), min(top, v.size()))};
}

struct Person {
  string name;
  int age, income;
  bool is_male;
};

vector<Person> ReadPeople(istream& input) {
  int count;
  input >> count;

  vector<Person> result(count);
  for (Person& p : result) {
    char gender;
    input >> p.name >> p.age >> p.income >> gender;
    p.is_male = gender == 'M';
  }

  return result;
}

vector<Person> sort_income(vector<Person> data){
    sort(
        data.begin(), data.end(), [](const Person& lhs, const Person& rhs) {
          return lhs.income > rhs.income;
        }
      );
      return data;
}


vector<Person> sort_age(vector<Person> data){
    sort(begin(data), end(data), [](const Person& lhs, const Person& rhs) {
      return lhs.age < rhs.age;
    });
      return data;
}


using GenderPair = std::pair<std::vector<Person>, std::vector<Person>>;

GenderPair sort_name(vector<Person> data){
 
  sort(data.begin(), data.end(), [](const Person& lhs, const Person& rhs) {
        return std::tie(lhs.is_male, lhs.name) < std::tie(rhs.is_male, rhs.name);
  });

   auto bound = partition(begin(data), end(data), [](const Person& p) {
      return p.is_male == false;
    }); 
  std::vector<Person> females(std::make_move_iterator(data.begin()), std::make_move_iterator(bound));  // Males (is_male == true)
  std::vector<Person> males(std::make_move_iterator(bound), std::make_move_iterator(data.end()));  // Females
  return std::make_pair(std::move(males), std::move(females));; 
}

const std::string* MostPopularName(const vector<Person>* sorted_gender) {
  const string* most_popular_name = &sorted_gender->begin()->name;
  int count = 1;
  for (auto i = sorted_gender->begin(); i != sorted_gender->end(); ) {
    auto same_name_end = find_if_not(i, sorted_gender->end(), [i](const Person& p) {
      return p.name == i->name;
    });
    auto cur_name_count = std::distance(i, same_name_end);
    if (cur_name_count > count) {
      count = cur_name_count;
      most_popular_name = &i->name;
    }
    i = same_name_end;
  }

  return most_popular_name;
}



int main() {
  
  vector<Person> people = ReadPeople(cin);
  
/*
  vector<Person> people = {
        {"Ivan", 25, 1000, true},
        {"Olga", 30, 623, false},
        {"Sergey", 24, 825, true},
        {"Maria", 42, 1254, false},
        {"Mikhail", 15, 215, true},
        {"Oleg", 18, 230, true},
        {"Denis", 53, 8965, true},
        {"Maxim", 37, 9050, true},
        {"Ivan", 47, 19050, true},
        {"Ivan", 17, 50, true},
        {"Olga", 23, 550, false}
    };
*/

  const vector<Person> sorted_age = [people]{
        vector<Person> data = sort_age(people);
        return data;
      }();

  const vector<Person> sorted_wealth = [people]{
        vector<Person> data = sort_income(people);
        return data;
      }();


  const GenderPair sorted_name = [people]{
      GenderPair data = sort_name(people);
      return data;
    }();

  const std::string* most_popular_name_m = MostPopularName(&sorted_name.first);
  const std::string* most_popular_name_f = MostPopularName(&sorted_name.second);



  
  for (string command; cin >> command; ) {
    if (command == "AGE") {
      int adult_age;
      cin >> adult_age;

      auto adult_begin = lower_bound(
        begin(sorted_age), end(sorted_age), adult_age, [](const Person& lhs, int age) {
          return lhs.age < age;
        }
      );
     
     cout << "There are " << (sorted_age.size() - (adult_begin - sorted_age.begin()) )
          << " adult people for maturity age " << adult_age << '\n';
    } else if (command == "WEALTHY") {
      int count;
      cin >> count;

      auto head = Head(sorted_wealth, count);
      
      int total_income = accumulate(
        head.begin(), head.end(), 0, [](int sum, const Person& p) {
          return sum += p.income;
        }
      );
      cout << "Top-" << count << " people have total income " << total_income << '\n';
    } else if (command == "POPULAR_NAME") {
      char gender;
      cin >> gender;  

      const vector<Person>& sorted_gender = (gender == 'M') ? sorted_name.first : sorted_name.second;

      if (sorted_gender.empty()) {
        cout << "No people of gender " << gender << '\n';
      } else {
        const string& most_popular_name = (gender == 'M') ? *most_popular_name_m : *most_popular_name_f;
        cout << "Most popular name among people of gender " << gender << " is " << most_popular_name << '\n';
        
      }
    }
  }
}
