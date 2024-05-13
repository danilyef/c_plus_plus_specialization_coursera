#### Programming Assignment "ConcurrentMap"

In the template solution for the "Synchronized Template" task, we briefly touched upon the idea that reducing the size of the critical section can increase the speed of a multithreaded program. In this task, we will further develop this idea.

Let's imagine that we have a map accessed by multiple threads. To synchronize access to it, we can protect each access to this map with a mutex (for example, by wrapping our map in the Synchronized template). Now let's imagine that we have a Synchronized<map<int, int>>, which contains all keys from 1 to 10000. Intuitively, when one thread accesses key 10, and another thread accesses, for example, key 6712, it seems unnecessary to protect these accesses with the same mutex. These are separate memory areas, and we do not modify the internal structure of the dictionary in any way. However, if we simultaneously access key 6712 from multiple threads, synchronization will undoubtedly be needed.

Hence the idea arises - to divide our dictionary into several sub-dictionaries with non-intersecting sets of keys and protect each of them with a separate mutex. Then, when different threads access different keys, they will not often fall into the same sub-dictionary, and therefore will be able to process it in parallel. You are tasked with implementing this idea in this assignment. You need to write a class template ConcurrentMap with the following interface:

```cpp
template <typename K, typename V>
class ConcurrentMap {
public:
  static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");

  struct Access {
    V& ref_to_value;
  };

  explicit ConcurrentMap(size_t bucket_count);

  Access operator[](const K& key);

  map<K, V> BuildOrdinaryMap();
};
```

The static_assert at the beginning of the class indicates that in this task it is assumed that the keys of ConcurrentMap can only be integers.

The constructor of the ConcurrentMap<K, V> class takes the number of sub-dictionaries into which all key space should be divided.

The operator[] should behave the same way as the analogous operator in map - if the key key is present in the dictionary, it should return an object of class Access containing a reference to the corresponding value; if key is absent in the dictionary, it should add the pair (key, V()) to it and return an object of class Access containing a reference to the newly added value.

The Access structure should behave the same way as in the Synchronized template - provide a reference to the dictionary value and ensure synchronized access to it.

The BuildOrdinaryMap method should merge together parts of the dictionary and return the entire dictionary as a whole. It should be thread-safe, meaning it should work correctly when other threads are performing operations on ConcurrentMap.