#### Programming task: First and last names ####

Implement a class for a person that maintains a history of the person's changes to their last name and first name.

```objectivec
class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    // add the fact that the name changed to first_name in the year year
  }
  void ChangeLastName(int year, const string& last_name) {
    // add the fact that the surname changed to last_name in the year year
  }
  string GetFullName(int year) {
    // get the first and last name as of the end of the year year
  }
private:
  // private field
};
```
Assume that in each year there can be no more than one change of surname and no more than one change of name. At the same time, over time, more and more facts from the person’s past can be discovered, so the years in successive calls to the *ChangeLastName* and *ChangeFirstName* methods do not have to increase.

It is guaranteed that all first and last names are non-empty.

The string returned by the *GetFullName* method must contain the person's first and last name, separated by a single space, as of the end of the given year.

* If there has been no last name or first name change by the current year, return the string **"Incognito"**.
* If there was a last name change for the given year, but no first name change, return **"last_name with unknown first name"**.
* If there was a name change for the given year, but no last name change, return **"first_name with unknown last name"**.

##### Example #####
###### Code ######
```objectivec
int main() {
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  return 0;
}
```

###### Output ######
```objectivec
Incognito
Polina with unknown last name
Polina Sergeeva
Polina Sergeeva
Appolinaria Sergeeva
Polina Volkova
Appolinaria Volkova
```

Unlike the *GetFullName* method, the *GetFullNameWithHistory* method must return not only the last first and last name by the end of the current year, but also all previous first and last names in reverse chronological order. If the current facts indicate that a person changed his last name or first name to the same two times in a row, the second change should be ignored when forming the story.

##### Example 2 #####
###### Code ######
```objectivec
int main() {
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1990, "Polina");
  person.ChangeLastName(1990, "Volkova-Sergeeva");
  cout << person.GetFullNameWithHistory(1990) << endl;
  
  person.ChangeFirstName(1966, "Pauline");
  cout << person.GetFullNameWithHistory(1966) << endl;
  
  person.ChangeLastName(1960, "Sergeeva");
  for (int year : {1960, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeLastName(1961, "Ivanova");
  cout << person.GetFullNameWithHistory(1967) << endl;
  
  return 0;
}
```

###### Output ######
```objectivec
Incognito
Polina with unknown last name
Polina Sergeeva
Polina Sergeeva
Appolinaria (Polina) Sergeeva
Polina Volkova (Sergeeva)
Appolinaria (Polina) Volkova (Sergeeva)
Polina (Appolinaria, Polina) Volkova-Sergeeva (Volkova, Sergeeva)
Pauline (Polina) with unknown last name
Sergeeva with unknown first name
Pauline (Polina) Sergeeva
Pauline (Polina) Sergeeva (Ivanova, Sergeeva)
```