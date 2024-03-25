#### Programming Assignment "StackVector"

Condition
In the memory model section, we discussed that dynamic memory is needed to store objects that should live longer than the function that created them. Moreover, we mentioned that it is possible to create a vector that does not use heap memory but instead stores all its objects on the stack. In this task, you will have to do this. You have recently become acquainted with the array container, which stores all its data on the stack. Implement the vector interface on top of it. More formally, implement the class template `template <typename T, size_t N> StackVector<T, N>`, where T is the type of the vector element, and N is its maximum capacity. The StackVector class should have the following interface:

```cpp
template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0);

  T& operator[](size_t index);
  const T& operator[](size_t index) const;

  ??? begin();
  ??? end();
  ??? begin() const;
  ??? end() const;

  size_t Size() const;
  size_t Capacity() const;

  void PushBack(const T& value);
  T PopBack();
};
```

The Capacity method should return the capacity of the vector, i.e., the number of objects that can theoretically fit into it.

The Size method should return the current number of objects in the vector.

The constructor takes the size of the vector (similarly to the standard vector). If the constructor argument is greater than the vector's capacity, the constructor should throw an invalid_argument exception.

The begin/end methods should return iterators to the beginning and current end of the vector; their type is not specified, you should choose it yourself.

The PushBack method adds a new element to the end of the vector. If the current size of the vector equals its capacity, the PushBack method should throw a standard overflow_error exception.

The PopBack method reduces the size of the vector by one and returns the last element of the vector. If the vector is empty, the PopBack method should throw a standard underflow_error exception.

The interface of the StackVector class is described in the stack_vector.h file attached to this task. Some of the requirements for it are formulated as unit tests in the stack_vector.cpp file.

Note the difference in behavior of the PushBack method in the StackVector class from the PushBack method in the SimpleVector class, which you implemented earlier in the memory model section. SimpleVector::PushBack allocated additional memory on the heap if the vector size equaled its capacity. In the case of the StackVector class, we must specify the maximum capacity of the vector at compile time, and if it is exhausted, we have nowhere else to take memory from, so we simply throw an exception. This is the disadvantage of implementing a stack-based vector compared to a regular vector.

On the other hand, the stack_vector.cpp file contains a benchmark that demonstrates the advantage of StackVector over a regular vector. This benchmark simulates a situation where we read N objects from a stream and then add N objects to the vector using the push_back method (test data is stored in vector<vector<int>> to exclude parsing time from the benchmark). When you implement the StackVector template, compare its performance with that of the vector.

Submit a header file with the implementation of the StackVector template for verification.