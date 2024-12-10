### Grouping Strings by Prefix: Part 1. Grouping by Character

Write a function called FindStartsWith:

- It takes a sorted set of strings represented by iterators range_begin and range_end and a single character prefix.
- It returns a range of strings that start with the character prefix as a pair of iterators.



```objectivec
template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    char prefix);

```

If the resulting range is empty, its boundaries should point to the position in the container where you can insert any string that starts with the character prefix without violating the sorting order (similar to the equal_range algorithm). It is guaranteed that the strings consist only of lowercase Latin letters, and the prefix character is also a lowercase Latin letter.

The search should be carried out with logarithmic complexity, for example, using binary search.


```objectivec
int main() {
  const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};

  const auto m_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
  for (auto it = m_result.first; it != m_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;

  const auto p_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
  cout << (p_result.first - begin(sorted_strings)) << " " <<
      (p_result.second - begin(sorted_strings)) << endl;

  const auto z_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
  cout << (z_result.first - begin(sorted_strings)) << " " <<
      (z_result.second - begin(sorted_strings)) << endl;

  return 0;
}

```