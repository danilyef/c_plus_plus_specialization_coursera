#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <numeric>
#include <functional>


using namespace std;

struct DateComponents {
    int year;
    int month;
    int day;
};

DateComponents extract_date_components (std::tm& date){
    DateComponents date_components;
    date_components.year = date.tm_year + 1900;
    date_components.month = date.tm_mon + 1;
    date_components.day = date.tm_mday;
    return date_components;
}

int jdn (DateComponents& date_components){
    //precalculate numbers: https://en.wikipedia.org/wiki/Julian_day
    int a = std::floor((14 - date_components.month)/12);
    int y = date_components.year + 4800 - a;
    int m = date_components.month + 12 * a - 3;

    //calculate JDN:
    int jdn = date_components.day + std::floor((153 * m + 2)/5) + 365 * y + std::floor(y/4) - std::floor(y/100) + std::floor(y/400) - 32045;

    return jdn;

}

int day_number_calc (std::tm& date, std::tm& start_date, std::tm& end_date){

    //start date
    DateComponents start_date_components = extract_date_components(start_date);
    const int start_jdn = jdn(start_date_components);
    
    //end date
    DateComponents end_date_components = extract_date_components(end_date);
    const int end_jdn = jdn(end_date_components);

    //from tm structure into numbers
    DateComponents date_components = extract_date_components(date);
    int date_jdn = jdn(date_components);

    //calculate JDN according to start and end date
    int day_number = date_jdn - start_jdn;

    return day_number;
}




int main() {
    size_t Q = 0;
    size_t i = 0;
    cin >> Q;

    //vector of earnings
    std::vector<double> earnings(36524); // or 36525 
    std::cout.precision(25);

    //start date
    std::tm start_date;
    start_date.tm_year = 100;   // 2000 is 1900 years after 1900
    start_date.tm_mon = 0;      // January (0-based index)
    start_date.tm_mday = 1;     // 1st day of the month

    //end date
    std::tm end_date;
    end_date.tm_year = 199;   // 2000 is 1900 years after 1900
    end_date.tm_mon = 11;      // January (0-based index)
    end_date.tm_mday = 31;     // 1st day of the month



    while(i < Q){
        
        //variables for user input
        std::string command;
        std::string date1;
        std::string date2;

        //user input
        cin >> command >> date1 >> date2; //read users input
        
        //convert into date format yyyy-mm-dd
        std::istringstream date_stream_start(date1);
        std::istringstream date_stream_end(date2);

        std::tm date_1 = {};
        std::tm date_2 = {};

        date_stream_start >> std::get_time(&date_1, "%Y-%m-%d");
        date_stream_end >> std::get_time(&date_2, "%Y-%m-%d");

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
        ++i;

    }
    
    return 0;
    }