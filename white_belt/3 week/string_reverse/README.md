#### Programming Task: String ####

Implement a *ReversibleString* class that stores a string and supports *Reverse* methods to reverse a string and *ToString* methods to get a string.

##### Example #####
###### Code ######
```objectivec
int main() {
  ReversibleString s("live");
  s.Reverse();
  cout << s.ToString() << endl;
  
  s.Reverse();
  const ReversibleString& s_ref = s;
  string tmp = s_ref.ToString();
  cout << tmp << endl;
  
  ReversibleString empty;
  cout << '"' << empty.ToString() << '"' << endl;
  
  return 0;
}
```

###### Output ######
```objectivec
evil
live
""
```