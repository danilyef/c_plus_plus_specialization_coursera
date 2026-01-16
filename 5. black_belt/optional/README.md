### **Programming Assignment: Optional Task

In this task, you need to implement a template class `Optional` that behaves similarly to `std::optional` — it can either store a value or store a marker indicating the absence of a value.

The provided solution template contains declarations of the methods that you need to implement:

```
optional.h
optional
```

Please note that `Optional`, unlike `unique_ptr`, must store its data on the stack rather than in dynamic memory. This data should be initialized only when necessary (by default, an `Optional` object is created empty). To achieve this, you need to use *placement new* — an explicit instruction to the compiler to construct an object at a specified memory location. For example, you can construct a new object of type `T` in the memory block `data` like this:

```cpp
new (data) T();
```

You will need to manage the lifetime of such an object manually. The raw memory `data` itself will be freed automatically, but you must explicitly call the destructor:

```cpp
reinterpret_cast<T*>(data)->~T();
```

**Remember:** constructing an object using placement new in already allocated memory, as in this task, is the *only* case where you need to call the destructor manually. Try not to create unnecessary objects of type `T`. For example, when assigning a new value to an already initialized `Optional`, simply call the appropriate assignment operator of type `T`.

For grading, submit a `.cpp` or `.h` file containing the implementation of the `Optional` template.

**Note.** The real `std::optional` is implemented in a more complex way. It cannot simply construct an object in a byte buffer on the stack, because then such a `std::optional` could not be used in `constexpr` expressions. Instead, the standard `std::optional` uses a `union`. However, for this task, using a regular buffer is completely sufficient.


