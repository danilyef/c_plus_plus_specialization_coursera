#### Programming Task: Moving Lines ####

Write a *MoveStrings* function that takes two vectors of strings, *source* and *destination*, and appends all strings from the first vector to the end of the second. After the function is executed, the *source* vector must be empty.


##### Example #####
```objectivec
vector<string> source = {"a", "b", "c"};
vector<string> destination = {"z"};
MoveStrings(source, destination);
// source must be empty
// destination must contain "z", "a", "b", "c" in this specific order
```