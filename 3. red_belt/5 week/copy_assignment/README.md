### Programming Assignment: Assignment Operator for SimpleVector

In the lecture, we acquainted ourselves with the copy constructor and the assignment operator, and also wrote a copy constructor for SimpleVector. In this task, you need to implement the assignment operator for SimpleVector.

Recall that the following code calls the copy constructor:

```
SimpleVector<int> source(5);
SimpleVector<int> dest = source; // Copy constructor
```

And the code below is the assignment operator:

```
SimpleVector<int> source(5);
SimpleVector<int> dest;
dest = source; // Assignment operator
```

You are given a cpp file that includes the header file simple_vector.h and contains a small set of unit tests. Submit for review the simple_vector.h file with the implementation of the assignment operator.