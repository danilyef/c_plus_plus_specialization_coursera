#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <tuple>
#include <utility>
#include <iomanip>

using namespace std;

class Date {
public:

    Date(int year, int month, int day);
    int GetYear() const;
    int GetMonth() const;
    int GetDay()const;
    std::string to_string() const;

private:
    int year_;
    int month_;
    int day_;

};



Date ParseDate(std::istream& is);

std::ostream& operator<<(std::ostream& os, const Date& obj);
std::ostream& operator<< (std::ostream& os, const std::pair<Date, std::string>& pair);

bool operator<(const Date& lhs,const Date& rhs);
bool operator<=(const Date& lhs,const Date& rhs);
bool operator>(const Date& lhs,const Date& rhs);
bool operator>=(const Date& lhs,const Date& rhs);
bool operator==(const Date& lhs,const Date& rhs);
bool operator!=(const Date& lhs,const Date& rhs);