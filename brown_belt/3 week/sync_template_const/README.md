#### Programming Task: "Constancy in the Synchronized Template 

**Note:**
This task is a continuation of the task "Synchronized Template" from the "Red Belt in C++." Below is its full description with the necessary additions. Therefore, if you haven't completed the "Red Belt," you can simply solve this task from scratch.

**Additional requirements compared to "Red Belt in C++":**

You need to add a constant method `GetAccess`, which returns an object containing a constant reference to the stored object.

**Problem Statement:**
As is well known, the lack of synchronization when multiple threads access the same data can have a fatal impact on a program's performance. Therefore, it is very important not to forget to lock a mutex when accessing shared data. However, if we have a large project where access to shared data is done in many places in the code, it’s not too hard to forget to do so while making edits.

To protect against such forgetfulness, you can write a special wrapper around the data that will only provide access to it under a mutex. In this task, you need to develop such a wrapper—a class template `Synchronized` with the following interface:

```cpp
template <typename T>
class Synchronized {
public:
  explicit Synchronized(T initial = T());

  Access1 GetAccess();
  Access2 GetAccess() const;
private:
  T value;
};
```

`Access1` and `Access2` types must be structures that contain the fields `T& ref_to_value` and `const T& ref_to_value`, respectively. In both cases, the `ref_to_value` field should refer to the `value` field of the `Synchronized<T>` class. Moreover, objects of the `Access1` and `Access2` classes should behave similarly to the `lock_guard<mutex>` class: they should lock the mutex in their constructor and release it in their destructor. Example:

```cpp
Synchronized<int> s_int;
{
  auto access = s_int.GetAccess();
  // Critical section starts here and continues until the end of the block
  access.ref_to_value = 5;
}
ASSERT_EQUAL(s_int.GetAccess().ref_to_value, 5);
```

You may (and should) add the necessary fields to the `Access1`, `Access2`, and `Synchronized` template classes. More detailed examples of the usage of the `Synchronized` template can be found in the solution template.

As you can see, the only way to access the `value` field of the `Synchronized<T>` class is to access the `ref_to_value` field of the `Access1` and `Access2` classes, which ensures that this access is performed under a mutex. Thus, if the shared data is wrapped in the `Synchronized` template, you will never forget to lock the mutex when accessing it.