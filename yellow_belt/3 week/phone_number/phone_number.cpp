#include "phone_number.h"
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;




PhoneNumber::PhoneNumber(const string &international_number){
    if(international_number[0] != '+'){
        throw invalid_argument("Number must start with +");
    }

    istringstream is(international_number);
    char delim = '-';
    
    char plus = is.get();
    getline(is,country_code_,delim);
    getline(is,city_code_,delim);
    getline(is,local_number_);

    if(country_code_.empty() || city_code_.empty() || local_number_.empty()){
        throw invalid_argument("Phone must include: country code, city code, local number! ");
    }


};

string PhoneNumber::GetCountryCode() const{
    return country_code_;
};
string PhoneNumber::GetCityCode() const{
    return city_code_;
};
string PhoneNumber::GetLocalNumber() const{
    return local_number_;
};
string PhoneNumber::GetInternationalNumber() const{
    return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
};



int main(){
    string s;
    cin >> s;
    PhoneNumber num(s);
    string country_code = num.GetCountryCode();
    string city_code = num.GetCityCode();
    string local_code = num.GetLocalNumber();
    string int_code = num.GetInternationalNumber();
    cout << country_code << endl;
    cout << city_code << endl;
    cout << local_code << endl;
    cout << int_code << endl;
}
