### Programming Task: Double Dispatch

**Theory — Static and Dynamic Type of a Pointer or Reference to an Object**

Let's consider a simple code example:

```cpp
class Unit;
class Building;
class Tower;
class Fence;

struct GameObject {
  virtual ~GameObject() = default;

  virtual bool Collide(const GameObject& that) const = 0;
  virtual bool CollideWith(const Unit& that) const = 0;
  virtual bool CollideWith(const Building& that) const = 0;
  virtual bool CollideWith(const Tower& that) const = 0;
  virtual bool CollideWith(const Fence& that) const = 0;
};
```

Our task is to implement the function `bool Collide(const GameObject& first, const GameObject& second)`, which checks whether two game objects collide, i.e., whether they have at least one common point.

You are given:

- The file `game_object.h`, containing the `GameObject` interface and the declaration of the `Collide` function.
  
- The files `geo2d.h/cpp`, containing a library for working with geometric figures on the plane. The library consists of the classes `Point`, `Rectangle`, `Circle`, and `Segment`, and a set of `Collide` functions that can determine intersections for each pair of figures (an interesting fact — all functions are implemented using integers, without any floating-point computations).
  
- The file `collide.cpp`, containing a solution template and a unit test that simulates placing a new object on the game map.

Submit to the testing system a file `collide.cpp` that will:

- Include `game_object.h`.

- Contain the implementations of the classes `Unit`, `Building`, `Tower`, and `Fence` (all of them must inherit from `GameObject` and implement its interface).

- Contain the implementation of the function `bool Collide(const GameObject& first, const GameObject& second)`, which returns `true` if the objects `first` and `second` have at least one common point on the plane, and `false` otherwise.

**Note**

One way to implement the `Collide` function is to use `dynamic_cast`. We did not cover this in lectures. Moreover, this approach leads to sprawling code prone to errors. We want you to thoroughly understand the concepts of static and dynamic types and to work with the `this` pointer in this task. Therefore, we will compile your solutions with the `-fno-rtti` flag, which will result in compilation errors if `dynamic_cast` is used.