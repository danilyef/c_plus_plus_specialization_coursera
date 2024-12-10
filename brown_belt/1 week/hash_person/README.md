### Programming Task: Integrating the Person Structure into an unordered_set

We want to learn how to integrate the Person structure into the unordered_set<Person, PersonHasher> container. To do this, you need to implement the PersonHasher and AddressHasher structures, as well as the comparison operators:

```cpp
struct Address {
  string city, street;
  int building;

  bool operator==(const Address& other) const {
    // implement the operator
  }
};

struct Person {
  string name;
  int height;
  double weight;
  Address address;

  bool operator==(const Person& other) const {
    // implement the operator
  }
};

struct AddressHasher {
  // implement the structure
};

struct PersonHasher {
  // implement the structure
};
```

To achieve this, use the standard hash functions `std::hash` and combine the field hashes using a polynomial, as demonstrated in the lecture.

### Requirements:
1. The hash functions should depend on all fields of the structures.
2. The hash function should distribute Person objects uniformly; this property is checked by the TestDistribution test in the solution template.