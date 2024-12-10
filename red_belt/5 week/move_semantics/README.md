### Programming Task: Move Semantics in SimpleVector

Solve the task "Implement your own vector" with the following additional requirements:

The PushBack method should allow adding an element to the vector using move semantics.

No vector methods should perform copying of elements.

Thus, a vector should be obtained that allows storing non-copyable objects.

The solution template includes a unit test that checks the operation of a vector consisting of non-copyable strings. If the vector performs copying, thanks to the specified unit test, the solution will not compile.