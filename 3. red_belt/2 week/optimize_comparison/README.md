### Optimize comparison

In this task, it is necessary to optimize the code used for sorting students by their rating. The data for each student is stored in the Student structure, declared in the student.h file. The student's rating is recorded in the rating field:

```cpp
struct Student {
  string first_name;
  string last_name;
  map<string, double> marks;
  double rating;

  bool operator < (const Student& other) const {
    return GetName() < other.GetName();
  }

  bool Less(const Student& other) const {
    return rating > other.rating;
  }

  string GetName() const {
    return first_name + " " + last_name;
  }
};
```

To sort students by rating, a comparison function is used, which returns true if the rating of the first student is higher than the rating of the second student.

```cpp
bool Compare(Student first, Student second) {
  return first.Less(second);
}
```

It has been identified that this function is the bottleneck in the sorting process, and it is specifically this function that needs to be optimized.