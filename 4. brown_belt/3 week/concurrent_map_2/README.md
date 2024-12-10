### Programming Assignment: Const Correctness in the ConcurrentMap Template

**Note:**
We have already added const correctness to the `Synchronized` template, which was developed in the "C++ Red Belt". Now, it's time to apply similar improvements to another template from the "Basic Multithreading" module—`ConcurrentMap`. Since we originally created this in the "C++ Red Belt", we've studied two important topics—unordered containers and mutable fields. We will now use this knowledge to bring `ConcurrentMap` closer to an industrial-grade implementation.

This task is a continuation of the "ConcurrentMap" task from the "C++ Red Belt". Below is the full description with necessary modifications. So, if you haven't completed the "Red Belt", you can tackle this task from scratch. Additional requirements compared to the "C++ Red Belt":

- Use an unordered container inside the class instead of `std::map`.
- Support arbitrary key types, not just integers.
- Add const methods `Has` and `At`.
- Make the `BuildOrdinaryMap` method const.

**Problem Statement:**
Let's imagine we have an `unordered_map` accessed by multiple threads. To synchronize access, we could protect each access to this `unordered_map` with a mutex (e.g., by wrapping our `unordered_map` in a `Synchronized` template). Now, imagine we have a `Synchronized<unordered_map<int, int>>` containing all keys from 1 to 10,000. Intuitively, if one thread accesses key 10 and another accesses key 6712, there's no need to protect these accesses with the same mutex. These are separate memory regions, and we aren't modifying the internal structure of the map. However, if multiple threads access key 6712 simultaneously, synchronization is certainly needed.

This leads to the idea of splitting our map into several sub-maps with non-overlapping key ranges, protecting each with a separate mutex. When different threads access different keys, they will rarely end up in the same sub-map, allowing them to process their operations in parallel. This is the idea you'll need to implement in this task. You are to write a `ConcurrentMap` class template with the following interface:

```cpp
template <typename K, typename V, typename Hash = std::hash<K>>
class ConcurrentMap {
public:
  using MapType = unordered_map<K, V, Hash>;

  struct WriteAccess {
    V& ref_to_value;
  };

  struct ReadAccess {
    const V& ref_to_value;
  };

  explicit ConcurrentMap(size_t bucket_count);

  WriteAccess operator[](const K& key);
  ReadAccess At(const K& key) const;

  bool Has(const K& key) const;

  MapType BuildOrdinaryMap() const;

private:
  Hash hasher;
};
```

The `ConcurrentMap<K, V>` class constructor accepts the number of sub-maps to split the entire key space into.

The `operator[]` should behave like the corresponding operator in `unordered_map`—if the key is present in the map, it should return a `WriteAccess` object containing a reference to the corresponding value. If the key is not present, it should add the pair `(key, V())` to the map and return a `WriteAccess` object containing a reference to the newly added value.

The `At` method should behave like the corresponding method in `unordered_map`—if the key is present, it should return a `ReadAccess` object containing a constant reference to the corresponding value. If the key is not present, `At` should throw a `std::out_of_range` exception.

The `WriteAccess` and `ReadAccess` structures should behave like in the `Synchronized` template, providing a reference to the map's value and ensuring synchronized access to it.

The `BuildOrdinaryMap` method should merge the sub-maps and return the entire map as a whole. It must be thread-safe, meaning it should work correctly while other threads are performing operations with `ConcurrentMap`. Unlike the task in the "C++ Red Belt", this method is made const in this task.

The `Has` method should safely check if the provided key is present in the map.

The third template parameter, `Hash`, is used for hashing keys of type `K`. Its interface is similar to `std::hash`—it's a class with a constant `size_t operator()(const K& key)`.