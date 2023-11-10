#### Name Surnmae 4: binary search ####

Solve the "Names and Surnames - 1" problem more efficiently by using binary search in the Person::GetFullName method. Let's recall the problem statement.

Implement a class for a person that supports a history of changes to their last name and first name.

Assume that in each year, there can be at most one change of last name and at most one change of first name. Moreover, new facts about the person's past may emerge over time, so the years in consecutive calls to the ChangeLastName and ChangeFirstName methods do not have to increase.

It is guaranteed that all names and surnames are non-empty.

The string returned by the GetFullName method should contain the person's first name and last name separated by a single space as of the end of the given year.

If there have been no changes to the last name or first name up to the given year, return the string "Incognito."

If there has been a change to the last name by the given year but no change to the first name, return "last_name with unknown first name."

If there has been a change to the first name by the given year but no change to the last name, return "first_name with unknown last name."

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
