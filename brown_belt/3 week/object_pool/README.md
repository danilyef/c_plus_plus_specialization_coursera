#### Programming Task: Object Pool

In practice, we often encounter objects whose creation takes significant time, such as threads, TCP connections, or database connections. Therefore, when such an object is no longer needed, it is not destroyed but set aside for later reuse. In this task, you are required to implement such a scheme — you need to write a class template `ObjectPool`:

```cpp
template <class T>
class ObjectPool {
public:
  T* Allocate();
  T* TryAllocate();

  void Deallocate(T* object);

  ~ObjectPool();

private:
  ...
};
```

An instance of the `ObjectPool` class should maintain two sets of objects: **allocated** and **freed** objects. Initially, both sets are empty.

The `Allocate` method should work as follows:

- If there is at least one freed object, it should be moved to the allocated set, and a pointer to it should be returned as the result of the function.
- If there are no freed objects, a new object should be created, added to the allocated set, and a pointer to it should be returned as the result of the function.

The `TryAllocate` method works similarly, but if there are no freed objects, it should simply return `nullptr`.

The `Deallocate` method moves the object from the allocated set to the freed set. If the passed object is not contained in the allocated set, the `Deallocate` method should throw an `invalid_argument` exception.

The `Allocate` and `TryAllocate` methods must return objects in **FIFO** order, meaning the freed set should represent a queue: the [Try]Allocate methods should retrieve objects from the front of the queue, and the `Deallocate` method should place the freed object at the end.

The destructor of the `ObjectPool` object should destroy all objects in the pool, both allocated and freed.