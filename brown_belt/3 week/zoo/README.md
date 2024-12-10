### Programming Task: Zoo
You are working with a class hierarchy that describes animals:

```cpp
#include <string>

class Animal {
public:
  virtual std::string Voice() const {
    return "Not implemented yet";
  }
  virtual ~Animal() {
  }
};

class Tiger: public Animal {
  std::string Voice() const override {
    return "Rrrr";
  }
};

class Wolf: public Animal {
  std::string Voice() const override {
    return "Wooo";
  }
};

class Fox: public Animal {
  std::string Voice() const override {
    return "Tyaf";
  }
};
```

You need to define a type `Zoo`, which represents a collection of various animals, and write two functions:

```cpp
Zoo CreateZoo(std::istream& in)

void Process(const Zoo& zoo, std::ostream& out)
```

- The `CreateZoo` function should read words from the input stream. If the input includes the words "Tiger", "Wolf", or "Fox", it should place the corresponding animal into the zoo. Otherwise, it should stop reading and generate an exception `std::runtime_error`.

- The `Process` function should iterate over all the animals in the zoo in the order of their creation and write the result of calling the `Voice` function for each one to the output stream.

---

### Notes:

- You don't need to rewrite the class code from `animals.h`; just include the `animals.h` header file.
- Be aware that in our version of `animals.h`, the animal sounds may differ from those shown in the example.
- Your program should create exactly as many animal objects as were passed in the input stream to the `CreateZoo` function.

---

Your task is to fix a solution that one of your friends wrote, but for some reason, it doesn't work. Correct it and submit it to the system.