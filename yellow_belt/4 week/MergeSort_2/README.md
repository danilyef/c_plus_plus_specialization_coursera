#### Merge Sort: Part 2 ####

Write a template function MergeSort that takes two iterators of template type RandomIt and sorts the range specified by them using merge sort. It is guaranteed that:

Iterators of type RandomIt are functionally similar to iterators of vectors and strings, meaning they can be compared using the operators <, <=, >, and >=, as well as be subtracted and added to numbers;
Sortable objects can be compared using the < operator."

```objectivec
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end);
```

Algorithm:
The classical merge sort algorithm looks as follows:

1. If the range contains fewer than 2 elements, exit the function.
2. Create a vector containing all the elements of the current range.
3. Split the vector into 3 equal parts.
4. Call the MergeSort function for each part of the vector.
5. Merge the first two-thirds of the vector using the merge algorithm, saving the result in a temporary vector using back_inserter.
6. Merge the temporary vector from the previous step with the last third of the vector from step 2, replacing the original range with the resulting sorted range.


You must implement this exact algorithm and no other: the testing system will verify that you perform these actions with the elements precisely.


```objectivec
int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}

```
