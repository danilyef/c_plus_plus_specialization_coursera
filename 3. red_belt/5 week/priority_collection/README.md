### Programming Assignment: Priority Container

### Task Description
Implement a template container PriorityCollection that allows storing objects of non-copyable type and performing the following operations with them:

- add an element with zero priority;
- add a set of elements with zero priorities;
- increase the priority of a specified element by 1;
- extract the element with the maximum priority from the container.

Since adding an element involves moving it into the container, the method for increasing the priority cannot accept the element itself. Therefore, the method that adds elements should return some identifier for each of them, which can then be used to call other methods.

The type of the identifier — PriorityCollection::Id — should be chosen by you. It should be easily copyable, for example, a number, pointer, or iterator. Examples of defining and using the Id type can be found in the solution template.

### Class Structure
```cpp
template <typename T>
class PriorityCollection {
public:
  using Id = /* type used for identifiers */;

  // Add an object with zero priority
  // by moving it and return its identifier
  Id Add(T object);

  // Add all elements in the range [range_begin, range_end)
  // by moving them, writing the issued identifiers
  // to the range [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin);

  // Determine whether the identifier belongs to any
  // object stored in the container
  bool IsValid(Id id) const;

  // Get the object by identifier
  const T& Get(Id id) const;

  // Increase the priority of the object by 1
  void Promote(Id id);

  // Get the object with the maximum priority and its priority
  pair<const T&, int> GetMax() const;

  // Similar to GetMax, but removes the element from the container
  pair<T, int> PopMax();

private:
  // Private fields and methods
};
```

### Guarantees
- For elements of type T, move and comparison operations (==, !=, <) are defined. All operations on elements have constant complexity.

- All added elements are distinct, but an element that has been added and then extracted may be added again.

- The Get and Promote methods are always called with valid identifiers according to the IsValid method.

- The GetMax and PopMax methods are called only when there are elements in the container.

- If there are multiple elements with the same maximum priority, the one that was added later than the others should be selected and extracted.