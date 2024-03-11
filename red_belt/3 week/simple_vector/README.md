#### Task on Programming "Writing Our Vector"

Condition:
In the lectures, we have already started implementing our vector. In this task, you need to expand it: add the methods Size, Capacity, and PushBack. Send for verification the header file simple_vector.h, containing the declaration and definition of the SimpleVector class template:

```cpp
template <typename T>
class SimpleVector {
public:
  SimpleVector() = default;
  explicit SimpleVector(size_t size);
  ~SimpleVector();

  T& operator[](size_t index);

  T* begin();
  T* end();

  size_t Size() const;
  size_t Capacity() const;
  void PushBack(const T& value);

private:
  ...
};
```

Requirements:

- The Capacity method should return the current capacity of the vector—the number of elements that fit into the block of memory currently allocated by the vector.

- The Size method should return the number of elements in the vector.

- The PushBack method adds a new element to the end of the vector. If there is no free space in the currently allocated block of memory (i.e., Size() == Capacity()), the vector should allocate a block of size 2 * Capacity(), copy all elements into it, and delete the old block.

- The first call to the PushBack method for a newly created object should set the capacity to one.

- The PushBack method should have an amortized constant time complexity.

- The begin and end methods should return iterators pointing to the current beginning and end of the vector.

- In the destructor, the currently allocated block of memory, allocated by the vector, should be freed.

- Also, see additional requirements for the SimpleVector's operation in the unit tests in the attached solution template.