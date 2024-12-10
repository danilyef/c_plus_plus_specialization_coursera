### Programming Task: Element Reference 

Implement the template function _GetRefStrict_, which takes as input: _map_ and key value _k_. If there is no element by the _k_ key in the collection, then the function must throw the _runtime_error_ exception, otherwise return a reference to the element in the collection.

### Example:
```objectivec
map<int, string> m = {{0, "value"}};
string& item = GetRefStrict(m, 0);
item = "newvalue";
cout << m[0] << endl; // выведет newvalue
```