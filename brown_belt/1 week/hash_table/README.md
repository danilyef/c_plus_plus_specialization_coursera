### Programming Task: Hash Table

Now that you know how unordered containers are structured internally, you are asked to implement a simplified version of a hash table yourself. Implement the HashSet template:

```cpp
template <typename Type, typename Hasher>
class HashSet {
public:
  using BucketList = forward_list<Type>;

public:
  explicit HashSet(
      size_t num_buckets,
      const Hasher& hasher = {}
  );

  void Add(const Type& value);
  bool Has(const Type& value) const ;
  void Erase(const Type& value);
  const BucketList& GetBucket(const Type& value) const;
};
```

Requirements:

- At any point in time, your hash table should have exactly `num_buckets` buckets. Rehashing is not required.
- The `Add` method should not change the contents of the table if an element equal to the given one already exists in the table.
- The `Has` method should return `true` if and only if an element equal to the given one is in the table.
- The `Erase` method should remove an element equal to the given one from the table if it exists; otherwise, it should not change the contents of the table.
- The `GetBucket` method should return a reference to the bucket that would contain the given element, regardless of whether it is in the table or not.