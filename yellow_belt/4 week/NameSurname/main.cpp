#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <string>

using namespace std;


string FindByYear(const map<int,string>& hist_map,int year){
    string name;
    auto name_it = hist_map.upper_bound(year);
    if(name_it != hist_map.begin()){
        name = (--name_it)->second;
    }
    return name;
}


class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        name_hist[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        surname_hist[year] = last_name;
    }
    string GetFullName(int year) {

        const string name = FindByYear(name_hist,year);
        const string surname = FindByYear(surname_hist,year);

        if( name.empty() && surname.empty()){
            return "Incognito";
        } else if( name.empty() ){
            return surname + " with unknown first name";
        } else if(surname.empty()){
            return name + " with unknown last name";
        } else {
            return name + " " + surname;
        }

    }
private:
    map<int,string> name_hist;
    map<int,string> surname_hist;
};


int main() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
    }

    return 0;
}

