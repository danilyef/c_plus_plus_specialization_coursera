#### Programming Task: Integrating the Point Structure into an unordered_set

We want to learn how to integrate the Point3D structure into the unordered_set<Point3D, Hasher> container. To do this, you need to implement the Hasher structure and the comparison operator:

```cpp
using CoordType = int;

struct Point3D {
  CoordType x;
  CoordType y;
  CoordType z;

  bool operator==(const Point3D& other) const {
    // implement the operator
  }
};

struct Hasher {
  // implement the structure
};
```

In your implementation, use the standard hash function `std::hash<CoordType>` for hashing the coordinates and combine the resulting hashes using a polynomial, as demonstrated in the lecture.

#### Requirements:
1. The hash function should depend on all the coordinates of the point.
2. The hash function should distribute the points uniformly in three-dimensional space; this property is checked by the TestDistribution test in the solution template.