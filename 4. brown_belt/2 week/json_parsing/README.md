### Programming Assignment Loading Expenses from JSON Format

In this training exercise, you need to support the loading of expenses from the JSON format into our personal finance management program. You should use a pre-existing library for working with JSON. Specifically, you need to write a function `vector<Spending> LoadFromJson(istream& input)`. `Spending` is a structure from the introductory lecture:

```cpp
struct Spending {
  string category;
  int amount;
};
```

The input stream contains the description of expenses in JSON format, for example:

```json
[
  {"amount": 2500, "category": "food"},
  {"amount": 1150, "category": "transport"},
  {"amount": 5780, "category": "restaurants"},
  {"amount": 7500, "category": "clothes"},
  {"amount": 23740, "category": "travel"},
  {"amount": 12000, "category": "sport"}
]
```

Important to note:

- The format of the text in the input stream is always exactly as in the example: there is an array containing several dictionaries with the keys "amount" and "category".
- The `Load` function from the provided JSON handling library can load the format described above.
- We are providing you with not a real JSON parsing library, but only minimal code sufficient to work with the described data format.
- The goal of this task is not to show how to properly parse JSON, but to familiarize you with the code that we will later use to discuss namespaces. Therefore, it is very important that you implement the `LoadFromJson` function using the contents of our JSON handling library.