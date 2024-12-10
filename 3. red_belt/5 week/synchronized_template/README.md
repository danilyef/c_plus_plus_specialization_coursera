### Programming Task: Synchronized Template

We have seen multiple times that the lack of synchronization of access by multiple threads to the same data can fatally affect the program's operation. Therefore, it is very important not to forget to acquire a mutex when accessing shared data. But if we have a large project where access to shared data is done from many places in the code, it's not that difficult to forget to do so when making changes.

To protect ourselves from such forgetfulness, we can write a special wrapper around the data, which will provide access to them only under a mutex. In this task, you need to develop such a wrapper - a class template named Synchronized with the following interface:

```cpp
template <typename T>
class Synchronized {
public:
  explicit Synchronized(T initial = T());

  struct Access {
    T& ref_to_value;
  };

  Access GetAccess();
private:
  T value;
};
```

The Access type should be a structure with a field `T& ref_to_value`, referring to the `value` field of the `Synchronized<T>` class. In addition, an object of the Access class should behave similarly to the `lock_guard<mutex>` class: it acquires the mutex in its constructor and releases it in its destructor. For example:

```cpp
Synchronized<int> s_int;
{
  auto access = s_int.GetAccess();
  // The critical section starts here and continues until the end of the block
  access.ref_to_value = 5;
}
ASSERT_EQUAL(s_int.GetAccess().value, 5);
```

You can (and should) add necessary fields to the Access class and the Synchronized template. For more detailed examples of using the Synchronized template, see the solution template.

As you can see, the only way to access the `value` field of the `Synchronized<T>` class is to access the `ref_to_value` field of the `Access` class, which guarantees that this access is performed under a mutex. Thus, if you wrap shared data in the Synchronized template, you will never forget to acquire the mutex when accessing them.