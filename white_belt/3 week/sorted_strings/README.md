#### Programming Task: Sorted Strings ####

Implement a class that maintains a set of rows in sorted order. The class must contain two public methods:
```objectivec
class SortedStrings {
public:
  void AddString(const string& s) {
    // add string s to set
  }
  vector<string> GetSortedStrings() { 
    // get a set of all added rows in sorted order
  }
private:
  // private fields
};
```

##### Example #####
###### Code ######
```objectivec
void PrintSortedStrings(SortedStrings& strings) {
  for (const string& s : strings.GetSortedStrings()) {
    cout << s << " ";
  }
  cout << endl;
}

int main() {
  SortedStrings strings;
  
  strings.AddString("first");
  strings.AddString("third");
  strings.AddString("second");
  PrintSortedStrings(strings);
  
  strings.AddString("second");
  PrintSortedStrings(strings);
  
  return 0;
}
```

###### Output ######
```objectivec
first second third
first second second third
```