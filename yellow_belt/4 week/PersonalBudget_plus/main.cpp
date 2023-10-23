/*

"Personal Budget," starter plus version
Implement a personal budget management system. You need to process requests of the following types:

date value: Consider that the amount value was earned on the specified date.
from to: Calculate the profit within the given date range.
First, you will receive queries with information about earnings, and then you will receive queries to calculate the profit.

Notes:

In all date ranges specified as from to, both the from and to dates are inclusive.
Input Format:
In the first line, you'll input the number of days with earnings information, denoted as E. Then, you'll input queries in the formats described above, one per line. Afterward, you'll input the number of profit calculation queries, denoted as Q. Finally, you'll input profit calculation queries, again in the specified formats, one per line.

Output Format:
For each profit calculation query, output an integer on a separate line, representing the profit for the specified date range.

Constraints:

The number of profit calculation queries, Q, is a natural number not exceeding 100,000.
All dates are provided in the format YYYY-MM-DD. The dates are valid (accounting for leap years) and belong to the interval from 1700 to 2099.
The value in earnings queries is a positive integer not exceeding 1,000,000.
The program should process all queries in 4.9 seconds.
Hint:
Use std::partial_sum to answer each query, calculating the difference between two partial sums.

Example:
Input:

3
2000-01-02 20
2000-01-06 10
2000-01-03 10
2
2000-01-01 2000-01-02
2000-01-02 2000-01-06

20
40

*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <numeric>
#include <chrono>

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

        const int year = std::stoi(day_components[0]);
        const int month = std::stoi(day_components[1]);
        const int day = std::stoi(day_components[2]);

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

int day_number_calc (const Date& date, int start_date_jdn){

    //date to calculate jdn
    int date_jdn = jdn(date);

    //calculate JDN according to start and end date
    int day_number = date_jdn - start_date_jdn;

    return day_number;
}


//start date
static const Date start_date = Date::from_string("1700-01-01");
static const int start_date_jdn = jdn(start_date);

//end date
static const Date end_date = Date::from_string("2099-12-31");
static const int end_date_jdn = jdn(end_date);

//difference in days between start date and end date:
static const size_t num_of_days = end_date_jdn - start_date_jdn;


int main() {

    //vector of earnings
    std::vector<int> earnings(num_of_days,0);
 
    size_t Q,E;
    cin >> E;

    //earning in particular day
    for(size_t i = 0; i!= E; ++i){
        
        //variables for user input
        std::string date;
        int sum;

        //user input
        cin >> date >> sum;//read users input

        //transform into date
        const Date date_earning = Date::from_string(date);

        //day number calculation
        int num_date_earning = day_number_calc(date_earning,start_date_jdn);

        //insert into vector
        earnings[num_date_earning] = sum;


    }

    cin >> Q;

    //income calculation
    for(size_t i = 0; i!= Q; ++i){
        
        //variables for user input
        std::string date1;
        std::string date2;

        //user input
        cin >> date1 >> date2; //read users input

        //transform into date
        const Date date_1 = Date::from_string(date1);
        const Date date_2 = Date::from_string(date2);

        //day number calculation
        int num_date_1 = day_number_calc(date_1,start_date_jdn);
        int num_date_2 = day_number_calc(date_2,start_date_jdn);

        //vector<int> temp;
        //std::partial_sum(earnings.begin() + num_date_1, earnings.begin() + num_date_2 + 1,  std::back_inserter(temp));
        //std::cout <<  temp.back() << std::endl;
        std::cout <<  std::accumulate(earnings.begin() + num_date_1, earnings.begin() + num_date_2 + 1, 0) << std::endl;
    }
    
        return 0;
    }