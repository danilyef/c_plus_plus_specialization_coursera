### Programming Assignment Loading Expenses from XML Format

In this practice problem, you need to support the loading of expenses from XML format into our personal finance management program. You should use an existing XML processing library. Specifically, you need to write a function `vector<Spending> LoadFromXml(istream& input)`. `Spending` is a structure introduced in the introductory lecture:

```cpp
struct Spending {
  string category;
  int amount;
};
```

The `input` stream contains an expense description in XML format, for example:

```xml
<july>
  <spend amount="2500" category="food"></spend>
  <spend amount="1150" category="transport"></spend>
  <spend amount="5780" category="restaurants"></spend>
  <spend amount="7500" category="clothes"></spend>
  <spend amount="23740" category="travel"></spend>
  <spend amount="12000" category="sport"></spend>
</july>
```

### Important notes:

- The text format in the `input` stream is always strictly as shown in the example: there is a single root node containing several `<spend>` nodes with "amount" and "category" attributes.
- The `Load` function from the provided XML library is capable of loading the format described above.
- We provide you with not a real XML parsing library, but only minimal code sufficient to work with the described data format.
- The goal of this task is not to show how to properly parse XML, but to familiarize you with the code on which we will later discuss namespaces. Therefore, it is very important that you implement the `LoadFromXml` function using the contents of our XML processing library.