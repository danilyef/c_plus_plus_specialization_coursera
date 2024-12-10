### Programming Assignment: Secondary Index in a Database

Data storage often requires fast search capabilities across any field. To achieve this, auxiliary data structures called secondary indexes are constructed to speed up searches. Implement such a storage for data of type `Record` as defined below:

```cpp
struct Record {
  string id;
  string title;
  string user;
  int timestamp;
  int karma;
};

class Database {
public:
  bool Put(const Record& record);
  const Record* GetById(const string& id) const;
  bool Erase(const string& id);

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const;

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const;

  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const;
};
```

**Requirements:**

1. **Put Operation:**
   - Should return `true` if the insertion is successful.
   - Should return `false` if the insertion fails because there is already a record with the same `id` in the database. In this case, the state of the database should not change.

2. **GetById Operation:**
   - Should return `nullptr` if there is no record with the specified `id` in the database.

3. **Erase Operation:**
   - Should return `true` if the element with the specified `id` was successfully deleted.
   - Should return `false` if the element with the specified `id` was not found. In this case, the state of the database should not change.

4. **Callback Function:**
   - Should return `true` if the iteration through the found records should continue.
   - Should return `false` otherwise. For example, this allows you to output the first 10 records or find the first record that meets an additional criterion.

5. **Performance:**
   - The time complexity for all operations should be sublinear on average (e.g., constant or logarithmic) relative to the total number of records in the database.

6. **Interval Boundaries:**
   - All interval boundaries are inclusive. The [low, high] interval request is the most universal; consider how to express conditions like `x < high`, `x > low`, and `x = x_0` using it.

While solving this task, you may assume that `bad_alloc` will not be thrown.