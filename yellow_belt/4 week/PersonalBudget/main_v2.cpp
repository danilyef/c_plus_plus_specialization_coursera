/*

"Personal Budget," starter version
Implement a personal budget management system. You need to process requests of the following types:

ComputeIncome from to: calculate the net income for the given date range.

Earn from to value: consider that the amount value was earned evenly over the specified period (per day).

Notes:

Both dates 'from' and 'to' are inclusive in all date ranges.

Input Format
The first line contains the number of queries Q, followed by the queries themselves in the format described above, one per line.

Output Format
For each ComputeIncome query, output a floating-point number in a separate line, representing the profit for the specified date range.

Note:

Use std::cout.precision(25) in your code for consistent formatting of floating-point numbers.

Constraints
The number of queries Q is a natural number not exceeding 50.

All dates are in the format YYYY-MM-DD. Dates are valid (accounting for leap years) and belong to the interval from 2000 to 2099.

Value is a positive integer not exceeding 1000000.

1 second for processing all queries.

*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <numeric>
#include <stdexcept>


using namespace std;


std::vector<string> SplitString(std::string& s_date){
    size_t pos = 0;
    std::string token;
    std::string delim = "-";
    std::vector<string> date_components;
    while ((pos = s_date.find(delim)) != std::string::npos) {
        token = s_date.substr(0, pos);
        date_components.push_back(token);
        s_date.erase(0, pos + delim.length());
    }
    date_components.push_back(s_date);
    return date_components;
};


class Date {
public:

    Date(int year, int month, int day) : year_(year), month_(month), day_(day) {};

    static Date from_string(std::string date_string){
        std::vector<string> day_components = SplitString(date_string);
        //check if Date consists of 3 elements
        if(day_components.size() != 3){
            throw std::runtime_error("Date consists of more than 3 components");
        }
        const int year = std::stoi(day_components[0]);
        const int month = std::stoi(day_components[1]);
        const int day = std::stoi(day_components[2]);
        
        //check in year, month and day are in ranges
        if( (year < 2000 || year > 2099) || (month < 1 || month > 12) || (day < 1  || day > 31)){
             throw std::runtime_error("Date in a wrong format");
        }
        return {year, month, day};
    }

    int GetYear() const {
        return year_;
    }

    int GetMonth() const {
        return month_;
    }

    int GetDay() const {
        return day_;
    }


private:
    int year_;
    int month_;
    int day_;

};



int jdn (const Date& date){
    //precalculate numbers: https://en.wikipedia.org/wiki/Julian_day
    int a = std::floor((14 - date.GetMonth())/12);
    int y = date.GetYear() + 4800 - a;
    int m = date.GetMonth() + 12 * a - 3;

    //calculate JDN:
    int jdn = date.GetDay() + std::floor((153 * m + 2)/5) + 365 * y + std::floor(y/4) - std::floor(y/100) + std::floor(y/400) - 32045;

    return jdn;

}

int day_number_calc (const Date& date, const Date& start_date,const Date& end_date){

    //start date
    int start_jdn = jdn(start_date);
    
    //end date
    int end_jdn = jdn(end_date);

    //entered date
    int date_jdn = jdn(date);

    //calculate JDN according to start and end date
    int day_number = date_jdn - start_jdn;

    return day_number;
}




int main() {

    //vector of earnings
    std::vector<double> earnings(36524,0.0); // or 36525 
    std::cout.precision(25);

    //start date
    const Date start_date = Date::from_string("2000-01-01");

    //end date
    const Date end_date = Date::from_string("2099-12-31");


    size_t Q;
    cin >> Q;

    for(size_t i = 0; i!= Q; ++i){
        
        //variables for user input
        std::string command;
        std::string date1;
        std::string date2;

        //user input
        cin >> command >> date1 >> date2; //read users input

        const Date date_1 = Date::from_string(date1);
        const Date date_2 = Date::from_string(date2);

        //day number calculation
        int num_date_1 = day_number_calc(date_1,start_date,end_date);
        int num_date_2 = day_number_calc(date_2,start_date,end_date);

        //functions execution:
        if (command == "Earn" ){
            double sum;
            std::cin >> sum;

            int range_days = num_date_2 - num_date_1 + 1;

            double split_earnings = sum / range_days;

            for(int i = num_date_1; i <= num_date_2; ++i){
                earnings[i] += split_earnings;
            }


        } else if (command == "ComputeIncome"){
            double income = std::accumulate(earnings.begin() + num_date_1, earnings.begin() + num_date_2 +1 ,0.0);
            std::cout << income << endl;
        }

    }
    
    return 0;
    }