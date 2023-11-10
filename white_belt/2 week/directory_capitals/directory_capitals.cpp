#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

void change_capital(map<string,string >& dict, const string& ctr, const string& cap){
    if(dict.count(ctr) == 0){
        cout << "Introduce new country " + ctr +  " with capital " + cap << endl;
        dict[ctr] = cap;
    } else if (cap == dict[ctr] && dict.count(ctr) >= 0){
        cout << "Country " + ctr + " hasn't changed its capital" << endl;
    } else{
        cout << "Country " + ctr + " has changed its capital from " +  dict[ctr] +  " to " + cap << endl;
        dict[ctr] = cap;
    }
    
}

void rename(map<string,string >& dict, const string& ctr_old, const string& ctr_new){
    if(ctr_old == ctr_new || dict.count(ctr_old) == 0 || dict.count(ctr_new) > 0){
        cout << "Incorrect rename, skip" << endl;
    } else{
        cout << "Country " + ctr_old + " with capital " + dict[ctr_old] + " has been renamed to " + ctr_new << endl;
        string temp_value = dict[ctr_old];
        dict.erase(ctr_old);
        dict[ctr_new] = temp_value;
    }
    
}


void about(map<string,string >& dict, const string& ctr){
    if(dict.count(ctr) == 0){
        cout << "Country " + ctr + " doesn't exist " << endl;
    } else{
        cout << "Country " + ctr + " has capital " + dict[ctr] << endl;
    }
}

void dump(const map<string,string >& dict){
    if(dict.size() == 0){
        cout << "There are no countries in the world" << endl;
    } else{
         for(auto item: dict){
            cout << item.first + "/" + item.second + " ";
        }
    }
    cout << endl; 
}


int main(){
    /*
    Q - number of operations
    operation - whih operation to perform
    country_new - new country for rename
    country_old - old country to rename
    country - country to get information about
    capital - capital of the country
    */
    int Q;
    string operation;
    map<string,string> dictionary; 
    cin >> Q;
    for(int i = 0;i< Q;i++){
        cin >> operation;
        if(operation == "CHANGE_CAPITAL"){
            string country, capital;
            cin >> country >> capital; 
            change_capital(dictionary, country, capital);

        } else if(operation == "RENAME"){
            string old_country, new_country;
            cin >> old_country >> new_country; 
            rename(dictionary, old_country, new_country);

        } else if(operation == "ABOUT"){
            string country;
            cin >> country;
            about(dictionary, country);

        } else if(operation == "DUMP"){
            dump(dictionary);
        }
        
        
    }
    return 0;
}