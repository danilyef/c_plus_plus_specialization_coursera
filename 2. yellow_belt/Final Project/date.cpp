#include "date.h"

using namespace std;

Date::Date(int year, int month, int day) : year_(year), month_(month), day_(day){};
int Date::GetYear() const {
    return year_;
};

int Date::GetMonth() const {
    return month_;
};
int Date::GetDay() const {
    return day_;
};

std::string Date::to_string() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) << year_ << '-';
    oss << std::setfill('0') << std::setw(2) << month_ << '-';
    oss << std::setfill('0') << std::setw(2) << day_;
    return oss.str();
};


Date ParseDate(std::istream& is){
    int year,month,day;
    char c;
    is >> year >> c >> month >> c >> day;
    return Date(year,month,day);
};



std::ostream& operator<<(std::ostream& os, const Date&date){

    os << std::setfill('0') << std::setw(4) << date.GetYear() << '-';
    os << std::setfill('0') << std::setw(2) << date.GetMonth() << '-';
    os << std::setfill('0') << std::setw(2) << date.GetDay();

    return os;
};

std::ostream& operator<<(std::ostream& os, const std::pair<Date, std::string>& pair){
    Date date = pair.first;
    std::string event = pair.second;

    os << date << " " << event;
    return os;
};

bool operator<(const Date& lhs,const Date& rhs){
    return std::make_tuple(lhs.GetYear(),lhs.GetMonth(),lhs.GetDay()) < std::make_tuple(rhs.GetYear(),rhs.GetMonth(),rhs.GetDay());
};

bool operator<=(const Date& lhs,const Date& rhs){
    return std::make_tuple(lhs.GetYear(),lhs.GetMonth(),lhs.GetDay()) <= std::make_tuple(rhs.GetYear(),rhs.GetMonth(),rhs.GetDay());
};

bool operator>(const Date& lhs,const Date& rhs){
    return std::make_tuple(lhs.GetYear(),lhs.GetMonth(),lhs.GetDay()) > std::make_tuple(rhs.GetYear(),rhs.GetMonth(),rhs.GetDay());
};

bool operator>=(const Date& lhs,const Date& rhs){
    return std::make_tuple(lhs.GetYear(),lhs.GetMonth(),lhs.GetDay()) >= std::make_tuple(rhs.GetYear(),rhs.GetMonth(),rhs.GetDay());
};


bool operator!=(const Date& lhs,const Date& rhs){
    return std::make_tuple(lhs.GetYear(),lhs.GetMonth(),lhs.GetDay()) != std::make_tuple(rhs.GetYear(),rhs.GetMonth(),rhs.GetDay());
};

bool operator==(const Date& lhs,const Date& rhs){
    return std::make_tuple(lhs.GetYear(),lhs.GetMonth(),lhs.GetDay()) == std::make_tuple(rhs.GetYear(),rhs.GetMonth(),rhs.GetDay());
};