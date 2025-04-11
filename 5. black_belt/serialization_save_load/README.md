### **Programming Assignment: Save & Load Task**

In the lectures, we saw that binary (de)serialization of a variable of a primitive type `T` (such as `int`, `char`, `double`, `bool`, etc.) is done like this:

```cpp
T x = ...;
output_stream.write(reinterpret_cast<const char*>(&x), sizeof(x));
input_stream.read(reinterpret_cast<char*>(&x), sizeof(x));
```

This approach is inconvenient for several reasons:

- The code is quite verbose;
- The variable name is used twice;
- The use of `reinterpret_cast` and raw pointers may raise concerns for someone reading the code.

Moreover, if we need to save the values of many variables (which is usually the case), the code becomes very hard to maintain. Finally, this binary serialization method generally doesn't work for complex types like structs and classes. 

So, in this task, we will develop a user-friendly library for binary (de)serialization of:

- Primitive types,
- Strings,
- Containers like `std::vector` and `std::map`.

### The interface of this library is extremely simple:

- If we have a variable `x` of type `T` and an output stream `output`, serialization is done via:
  ```cpp
  Serialize(x, output);
  ```

- If we have a variable `x` of type `T` and an input stream `input`, deserialization is done via:
  ```cpp
  Deserialize(input, x);
  ```

---

### Important Notes:

- The library must support (de)serializing nested containers, for example:  
  `std::vector<std::map<int, std::string>>`
  
- The function headers that you need to implement are provided in the `saveload.h` file.

- When serializing any container, first write a `size_t` number — the size of the container — and then write the elements themselves.

- For `std::map`, serialize elements as key-value pairs.

- `Deserialize` functions must reconstruct the original object from its serialized form.

---

### For example:

Let’s say we want to serialize the following:

```cpp
std::map<uint32_t, std::string> m = {
  {1, "hello"},
  {2, "bye"},
};
```

On a 64-bit little-endian platform (which your machine almost certainly is), the result should look like this (output shown using the Linux console utility `hd`, applied to the binary file):

```
00000000  02 00 00 00 00 00 00 00  01 00 00 00 05 00 00 00  |................|
00000010  00 00 00 00 68 65 6c 6c  6f 02 00 00 00 03 00 00  |....hello.......|
00000020  00 00 00 00 00 62 79 65                           |.....bye|
```

---

### For simplicity:

In this task, you **do not** need to account for **alignment** or **byte order (endianness)** — you can assume they will be the same during serialization and deserialization. You will learn more about these nuances in later parts of the course — for now, just don’t worry about them.

---

### Submission:

Please submit the `saveload.h` file containing the implementation of all `Serialize` and `Deserialize` functions.

---

Let me know if you’d like help implementing the functions in `saveload.h`!