#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

/*
Реализуйте класс для человека, поддерживающий историю изменений человеком своих фамилии и имени.
*/

class Person {
public:

    Person(const string& new_name, const string& new_surname,int new_year){
        person_year = new_year;
        ChangeFirstName(new_year, new_name);
        ChangeLastName(new_year, new_surname);
    }

    string get_name(const map<int,string>& m,int year) const{
        string name;
        for(const auto elem: m ) {
            if(elem.first <= year){
                name = elem.second;
            }
            else {
                break;
                }
            }
        return name;
    }

    vector<string> get_name_hist(const map<int,string>& m,int year) const{
        vector<string> names;
        vector<string> names_final;



        for(auto elem: m){
            if(elem.first <= year){
                names.push_back(elem.second);
            }
        }
        reverse(names.begin(),names.end());
       
        for(int i = 1;i <names.size();++i){
            if(count(names_final.begin(),names_final.end(),names[i]) == 0){
                names_final.push_back(names[i]);
            }  
        }

        
        return names_final;
    }


    string string_from_vec(const vector<string>& v) const{
        string s = " (";
        for(int i = 0;i< v.size();++i){
            s += v[i];
            s += ", ";
        }
        s.pop_back();
        s.pop_back();
        s += ")";
        return s;
    }

    void ChangeFirstName(int year, const string& first_name) {
        // добавить факт изменения имени на first_name в год year
        if(year >= person_year){
            person_name = first_name;
            name[year] = first_name;
        }
    }

    void ChangeLastName(int year, const string& last_name) {
        // добавить факт изменения фамилии на last_name в год year
        if(year >= person_year){
            person_surname = last_name;
            surname[year] = last_name;
        }
    }
    string GetFullNameWithHistory(int year) const{
    // вернуть имя и фамилию по состоянию на конец года year
        if(year < person_year){
            return "No person";
        }
        const string first_name = get_name(name,year);
        const string second_name = get_name(surname,year);
        
        vector<string> first_name_hist = get_name_hist(name,year);
        vector<string> second_name_hist = get_name_hist(surname,year);

        if(first_name_hist.size() > 0 && first_name_hist[0] == first_name){
            /*first_name_hist.pop_back();*/
            first_name_hist.erase(first_name_hist.begin());
        }

        if(second_name_hist.size() > 0 && second_name_hist[0] == second_name){
            /*second_name_hist.pop_back();*/
            second_name_hist.erase(second_name_hist.begin());
        }

        string history_fn = "";
        string history_sn = "";

        if(first_name.empty() && second_name.empty()){
            return "Incognito";
        } else if(first_name.empty()){

            if(second_name_hist.size() > 0){
                history_sn = string_from_vec(second_name_hist);
            } 
            return second_name +  history_sn + " with unknown first name";

        } else if(second_name.empty()){
           
           if(first_name_hist.size() > 0){
                history_fn = string_from_vec(first_name_hist);
            } 
            return first_name + history_fn + " with unknown last name";

        } else {

            if(second_name_hist.size() > 0){
                history_sn = string_from_vec(second_name_hist);
            } 

            if(first_name_hist.size() > 0){
                history_fn = string_from_vec(first_name_hist);
            } 

            return first_name + history_fn + " " + second_name + history_sn;
        }
    }

    string GetFullName(int year) const {
        // получить все имена и фамилии по состоянию на конец года year
        if(year < person_year){
            return "No person";
        }
        const string first_name = get_name(name,year);
        const string second_name = get_name(surname,year);

        if(first_name.empty() && second_name.empty()){
            return "Incognito";
        } else if(first_name.empty()){
            return second_name + " with unknown first name";
        } else if(second_name.empty()){
            return first_name + " with unknown last name";
        } else {
            return first_name + " " + second_name;
        }
    }
private:
    map<int,string> name;
    map<int,string> surname;
    string person_name;
    string person_surname;
    int person_year;
};



int main() {

	Person person("-1_first", "-1_last", -1);
	
	int year = 3;
	person.ChangeFirstName(year, std::to_string(year) + "_first");
	person.ChangeLastName(year, std::to_string(year) + "_last");

	year = 5;
	person.ChangeFirstName(year, std::to_string(year) + "_first");
	person.ChangeLastName(year, std::to_string(year) + "_last");

	year = 1;
	person.ChangeFirstName(year, std::to_string(3) + "_first");
	person.ChangeLastName(year, std::to_string(3) + "_last");

	year = 7;
	std::cout << "year: " << year << '\n';
	std::cout << person.GetFullNameWithHistory(year) << '\n';

	return 0;

}