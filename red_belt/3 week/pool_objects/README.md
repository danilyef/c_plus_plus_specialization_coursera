#### Task on Programming "Object Pool"

In practice, there are often objects that take a significant amount of time to create, such as threads, TCP connections, or database connections. Therefore, when such an object is no longer needed, it is not destroyed but rather set aside to be reused later. In this task, you are required to implement such a scheme — you need to write a template class called `ObjectPool`:

```cpp
template <class T>
class ObjectPool {
public:
  T* Allocate();
  T* TryAllocate();

  void Deallocate(T* object);

  ~ObjectPool();

private:
  // Implementation details go here
};
```

An object of the `ObjectPool` class should maintain two sets of objects: allocated and deallocated, both initially empty.

The `Allocate` method should work as follows:

- If there is at least one deallocated object, it should be moved to the set of allocated objects, and a pointer to it should be returned as the function's result.
- If there are no deallocated objects, a new object is created, placed in the set of allocated objects, and a pointer to it is returned as the function's result.

The `TryAllocate` method works similarly. However, if there are no deallocated objects, it should simply return `nullptr`.

The `Deallocate` method moves an object from the set of allocated objects to the set of deallocated objects. If the passed object is not in the set of allocated objects, the `Deallocate` method should throw an `invalid_argument` exception.

The `Allocate` and `TryAllocate` methods should return objects in FIFO order. In other words, the set of deallocated objects should represent a queue: the `[Try]Allocate` methods should extract objects from the beginning of it, and the `Deallocate` method should place the deallocated object at the end of the queue.

The destructor of the `ObjectPool` object should destroy all objects in the pool, both allocated and deallocated.