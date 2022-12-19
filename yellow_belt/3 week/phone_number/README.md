#### Programming Task: Implement the class declared in the header file ####
You are given a *phone_number.h* header file containing the *PhoneNumber* class declaration. At the same time, the comments describe the behavior that is expected from the implementation of this class.

[phone_number.h](https://github.com/Hitoku/basics-of-c-plus-plus-development-yellow-belt/blob/master/Week_3/02%20Programming%20Assignment/Source/phone_number.h)

```objectivec
#pragma once
#include <string>
using namespace std;
class PhoneNumber {
public:
  /* Accepts a string in the format +XXX-YYY-ZZZZZZ
     The part from '+' to the first '-' is the country code.
     The part between the first and second characters '-' is the area code
     Everything after the second '-' character is a local number.
     The country code, area code, and local number must not be empty.
     If the string does not conform to this format, an invalid_argument exception must be thrown. There is no need to check that the number contains only digits.
     Examples:
     * +7-495-111-22-33
     * +7-495-1112233
     * +323-22-460002
     * +1-2-coursera-cpp
     * 1-2-333 - invalid number - does not start with '+'
     * +7-1233 - invalid number - only country and area code
  */
  explicit PhoneNumber(const string &international_number);
  string GetCountryCode() const;
  string GetCityCode() const;
  string GetLocalNumber() const;
  string GetInternationalNumber() const;
private:
  string country_code_;
  string city_code_;
  string local_number_;
};
```