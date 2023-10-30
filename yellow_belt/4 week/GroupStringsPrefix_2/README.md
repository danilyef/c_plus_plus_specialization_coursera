#### Grouping Strings by Prefix: Part 2. Grouping by string ####

Grouping Strings by Prefix: Part 2
Write a more universal version of the FindStartsWith function that takes an arbitrary string consisting of lowercase Latin letters as a prefix.



```objectivec
template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    const string prefix);

```

If the resulting range is empty, its boundaries should point to the position in the container where you can insert any string that starts with the character prefix without violating the sorting order (similar to the equal_range algorithm). It is guaranteed that the strings consist only of lowercase Latin letters, and the prefix character is also a lowercase Latin letter.

The search should be carried out with logarithmic complexity, for example, using binary search.


```objectivec
int main() {
    const std::vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};

    const auto m_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
    for (auto it = m_result.first; it != m_result.second; ++it) {
        std::cout << *it << " ";
    }
    std::cout << endl;

    const auto p_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
    std::cout << (p_result.first - begin(sorted_strings)) << " " <<
        (p_result.second - begin(sorted_strings)) << endl;

    const auto z_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
    std::cout << (z_result.first - begin(sorted_strings)) << " " <<
        (z_result.second - begin(sorted_strings)) << endl;

    return 0;
}

```