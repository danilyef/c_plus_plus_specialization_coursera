#include <string>
#include <sstream> 
#include <iostream>
#include "phone_number.h"

using namespace std;


PhoneNumber::PhoneNumber(const string &international_number){
    if(international_number[0]  != '+'){
        throw invalid_argument("Phone number must start from +!");
    } else if(count(international_number.begin(),international_number.end(),'-') !=2){
        throw invalid_argument("Phone number contain two  '-' signs: + country_code - city_code - personal_number");
    }
    
    stringstream stream(international_number);
    const char sign = stream.get();

    getline(stream, country_code_, '-');
    getline(stream, city_code_, '-');
    getline(stream, local_number_, '\n');

	if (sign != '+' || country_code_.empty())
	{
		throw invalid_argument("The country code must begin with a + sign and be at least one character");
	}

	if (city_code_.empty())
	{
		throw invalid_argument("Area code cannot be empty");
	}

	if (local_number_.empty())
	{
		throw invalid_argument("Phone number cannot be empty");
	}
    
}


string PhoneNumber::GetCountryCode() const{
    return country_code_;
}
string PhoneNumber::GetCityCode() const{
    return city_code_;
}
string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}
string PhoneNumber::GetInternationalNumber() const{
    return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}



ostream& operator<<(ostream& stream, const PhoneNumber& pn){
    stream << "+" + pn.GetCountryCode() + "-" + pn.GetCityCode() + "-" + pn.GetLocalNumber();
    return stream;
}

int main(){

    PhoneNumber pn("+12-333");
    cout << pn;
}