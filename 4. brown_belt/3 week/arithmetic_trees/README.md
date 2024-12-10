### Programming Task: Expression Tree

In this task, we will use the smart pointer `unique_ptr` to manage the lifetime of a tree of polymorphic objects. Specifically, we will work with an arithmetic expression tree. The nodes of the tree will represent numbers and operations.

For example, the expression `"2*(3+4)"` will be represented by the following tree:

```
       *
      / \
     2   +
        / \
       3   4
```

In the program, the nodes of the tree are represented by objects of types inherited from the interface `Expression`, which is declared in the file `Common.h`. The interface has two methods:

- `Evaluate()` returns the numerical value of the expression. For our example, it will return `14`.
- `ToString()` formats the expression as a string. For simplicity of implementation, in order to ignore the precedence of operations, each node is enclosed in parentheses. Thus, for our example, this method will return `"(2)*((3)+(4))"`.

Since `Expression` is an abstract class, it can only be worked with through a pointer or a reference. To avoid manual memory management, we will use the smart pointer `unique_ptr`. To prevent cluttering the code with `unique_ptr<Expression>` expressions, a synonym `ExpressionPtr` is provided in the file `Common.h` for this expression.

You need to implement functions that allow creating such an expression tree. These are declared in the file `Common.h`, which is provided below:

- `Value()` returns a tree with a single node representing an integer.
- `Sum()` returns a new tree that represents the sum of two given expressions.
- `Product()` returns a new tree that represents the product of two given expressions.

Thus, the following code will create a tree for the expression `"2*(3+4)"`:

```cpp
Product(Value(2), Sum(Value(3), Value(4)));
```

Submit a `.cpp` file for verification, which:

1. Includes the header file `Common.h`.
2. Contains implementations of the functions `Product()`, `Value()`, and `Sum()`.