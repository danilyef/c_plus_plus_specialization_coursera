#### Programming Assignment "Linked List"

A linked list is a classic example of a data structure that requires the use of heap memory for implementation. In this task, you need to implement a class template called LinkedList, which represents a singly linked list and has the following interface:

```cpp
template <typename T>
class LinkedList {
public:
  struct Node {
    T value;
    Node* next = nullptr;
  };

  ~LinkedList();

  void PushFront(const T& value);
  void InsertAfter(Node* node, const T& value);
  void RemoveAfter(Node* node);
  void PopFront();

  Node* GetHead() { return head; }
  const Node* GetHead() const { return head; }

private:
  Node* head = nullptr;
};
```

The GetHead method returns a pointer to the head of the list, which is used for iterating through the list elements (see the ToVector template in the solution template).

The PushFront method adds a new element to the head of the list.

The InsertAfter method inserts a new element into the list so that it comes after the node specified. If node == nullptr, the method is equivalent to PushFront.

The PopFront method removes the element from the head of the list and frees the memory allocated for it. If the list is empty, the method terminates correctly. If the list becomes empty after the method execution, the GetHead method should return nullptr.

The RemoveAfter method should remove the element from the list that follows the node and free the memory allocated for it. If node == nullptr, the method is equivalent to PopFront. If node->next == nullptr, the method should terminate correctly.

All the methods listed above should work in O(1) time complexity.

The destructor of the LinkedList class frees all the memory allocated for storing the list elements.