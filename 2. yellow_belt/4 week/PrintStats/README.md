### Demographic Stats 

In this task, you need to calculate various demographic indicators for a group of people. A person is represented by the structure 'Person'

```objectivec
struct Person {
  int age;  // возраст
  Gender gender;  // пол
  bool is_employed;  // имеет ли работу
};

```

Gender is represented in the following way:

```objectivec
enum class Gender {
  FEMALE,
  MALE
};
```

You need to write a function named 'PrintStats' that takes a vector of people, calculates, and prints the median age for each of the following groups:

All people.
All females.
All males.
All employed females.
All unemployed females.
All employed males.
All unemployed males.
All 7 numbers should be output in strict accordance with the format (see the example).

By accepting the vector by value (rather than by constant reference), you gain the ability to modify its copy in any way, thus making calculations easier.


```objectivec
void PrintStats(vector<Person> persons);
```