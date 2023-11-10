/*

Solve the "Names and Surnames - 1" problem more efficiently by using binary search in the Person::GetFullName method. Let's recall the problem statement.

Implement a class for a person that supports a history of changes to their last name and first name.

Assume that in each year, there can be at most one change of last name and at most one change of first name. Moreover, new facts about the person's past may emerge over time, so the years in consecutive calls to the ChangeLastName and ChangeFirstName methods do not have to increase.

It is guaranteed that all names and surnames are non-empty.

The string returned by the GetFullName method should contain the person's first name and last name separated by a single space as of the end of the given year.

If there have been no changes to the last name or first name up to the given year, return the string "Incognito."

If there has been a change to the last name by the given year but no change to the first name, return "last_name with unknown first name."

If there has been a change to the first name by the given year but no change to the last name, return "first_name with unknown last name."
*/


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

