### Programming Task: Subset of the set 

Write a template function called FindGreaterElements that takes a set of elements of type T and another object of type T called "border". The function should return a vector of all the elements from the set that are greater than the "border" object, in ascending order.

```objectivec
template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border);

int main() {
  for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
    cout << x << " ";
  }
  cout << endl;
  
  string to_find = "Python";
  cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
  return 0;
}

```
