### Programming Task: Tests for the Person class 


### A task 
In the first course "White Belt in C ++" we had the task Names and Surnames - 1. In it, it was necessary to develop a _Person_ class that maintains a history of changes by a person to his last name and first name. In this task, you need to develop unit tests for the implementation of the _Person_ class. When developing tests, consider the restrictions imposed on the _Person_ class by the condition of the problem "Names and surnames - 1".

### Condition of the task "Names and surnames — 1" 
Implement a class for a person that maintains a history of the person's changes to their last name and first name.

```objectivec
class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
  }
  void ChangeLastName(int year, const string& last_name) {
  }
  string GetFullName(int year) {
  }
private:
};
```
Assume that in each year there can be no more than one change of surname and no more than one change of name. At the same time, over time, more and more facts from the person’s past can be discovered, so the years in successive calls to the _ChangeLastName_ and _ChangeFirstName_ methods do not have to increase.

It is guaranteed that all first and last names are non-empty.

The string returned by the _GetFullName_ method must contain the person's first and last name, separated by a single space, as of the end of the given year.

- If there has been no last name or first name change by the current year, return the string **"Incognito"**.
- If there was a last name change for the given year, but no first name change, return **"last_name with unknown first name"**.
- If there was a name change for the given year, but no last name change, return **"first_name with unknown last name"**.

