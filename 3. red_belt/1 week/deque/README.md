### Programming Assignment "Deque based on two vectors"

### Task
Write a template class Deque that contains the following set of methods:

- Default constructor;
- Constant method Empty, returning true if the deque does not contain any elements;
- Constant method Size, returning the number of elements in the deque;
- T& operator[](size_t index) and const T& operator[](size_t index) const;
- Constant and non-constant method At(size_t index), generating a standard out_of_range exception if the index is greater than or equal to the number of elements in the deque;
- Constant and non-constant versions of the methods Front and Back, returning references to the first and last elements of the deque, respectively;
- Methods PushFront and PushBack.

Non-constant versions of the methods should allow modifying the corresponding element of the deque.

To implement this, create two vectors inside the Deque class: insert into one in the PushFront method and into the other in the PushBack method.

### Note
The header file you submit for review should not include the <list>, <deque>, <set>, <map> files. If any of these files are included, you will receive a compilation error.