#### Programming Assignment: "set::iterator++"

In the lectures, you learned about the internal structure of the map and set containers. Typically, map and set are implemented as binary search trees.

You also learned how to traverse a tree using iterators.

In this task, we will not work with the set container, but with a similar binary search tree consisting of the following nodes:

```cpp
struct Node {
  int value;
  Node* left;
  Node* right;
  Node* parent;
};
```

Where:
- `value` is the value stored in the node;
- `left` and `right` are pointers to the child nodes (both are `nullptr` for the leaves of the tree);
- `parent` is a pointer to the parent node (it is `nullptr` for the root of the tree).

Let's assume that for tree traversal, we are using not a special iterator but simply a pointer to the node `Node*`.

You are required to implement the function

```cpp
Node* Next(Node* node);
```

that returns a pointer to the next node in ascending order of values.

The function should return `nullptr` if the current node is the last one in the tree.