### Programming Task: EnsureEqual Function 

Write functon
```objectivec
void EnsureEqual(const string& left, const string& right);
```

If the string **left** is not equal to the string **right**, the function must throw a runtime_error exception with the content "<l> != <r>", where <l> and <r> are the strings that are stored in the variables **left** and **right** respectively.
Note that there must be exactly one space around the inequality sign in the string that is placed in the exception.

If **left == right**, the function must complete correctly.

For example code

```objectivec
int main() {
  try {
    EnsureEqual("C++ White", "C++ White");
    EnsureEqual("C++ White", "C++ Yellow");
  } catch (runtime_error& e) {
    cout << e.what() << endl;
  }
  return 0;
}
```

must output

```objectivec
C++ White != C++ Yellow
```