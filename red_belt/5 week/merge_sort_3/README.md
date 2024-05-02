
#### Programming Assignment: Merge Sort - 3

Condition
Write a template function MergeSort, taking two iterators of a template type RandomIt and sorting the range specified by them using merge sort. It is guaranteed that:

iterators of type RandomIt are functionally similar to iterators of vectors and strings, meaning they can be compared using operators <, <=, >, and >=, as well as subtracted and added to numbers;
sortable objects can be compared using the < operator.

```cpp
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end);
```

Algorithm
In this task, you must implement the algorithm exactly as presented below; the testing system will check that you perform these actions with the elements:

If the range contains fewer than 2 elements, exit the function.
Create a vector containing all the elements of the current range.
Split the vector into three equal parts. (In this task, it is guaranteed that the length of the passed range is a power of three, so the vector can always be split into three equal parts.)
Call the MergeSort function on each part of the vector.
Merge the first two-thirds of the vector using the merge algorithm, saving the result in a temporary vector using back_inserter.
Merge the temporary vector from the previous step with the last third of the vector from step 2, writing the resulting sorted range instead of the original.
During the operation of your algorithm, there should be no copying of sortable elements. If you use copying, your solution will not compile when submitted for verification.