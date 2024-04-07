#### Programming Task: "String Grouping"

Write a review of the task and provide general instructions. If initial files are used in the task, include a link to them.

You are given a set of strings. It is necessary to group them so that each group contains strings with the same set of characters.

For example, if the strings given are "law", "port", "top", "laptop", "pot", "paloalto", "wall", and "awl", they should be grouped into 4 groups:

Strings consisting only of the letters 'a', 'l', and 'w': "law", "wall", "awl";
Strings consisting only of the letters 'o', 'p', 'r', and 't': "port";
Strings consisting only of the letters 'o', 'p', and 't': "top", "pot";
Strings consisting only of the letters 'a', 'l', 'o', 'p', and 't': "laptop", "paloalto".
The grouping should be implemented as a function:

```cpp
template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings);
```

Here, `Group<String>` is a synonym for `vector<String>`:

```cpp
template <typename String>
using Group = vector<String>;
```

Having such a synonym allows you to express the return type of the function `GroupHeavyString` as `vector<Group<String>>`, which is more readable than `vector<vector<String>>`.

The words in each group should be arranged in the same order as in the original set. The order of the groups themselves does not matter.

A string of type `String` does not have to consist of characters of type `char`. You can obtain the character type using the expression `typename String::value_type` or `Char<String>` if you define the corresponding synonym:

```cpp
template <typename String>
using Char = typename String::value_type;
```

The `String` type can be, for example, a regular string (`string`) or a vector of characters.

About the `Char<String>` type, the following is known:

Objects of this type can be compared using the `==` and `<` operators.

Not only the strings themselves can be "heavy," but also individual characters. Therefore, you can freely move them, but each character should be copied no more than once in the function (excluding copying when passing the `strings` argument by value). Otherwise, you will receive a "wrong answer" verdict with a corresponding comment.

Constraints:
The function must process a maximum of 100,000 strings with a length of no more than 100 within 1 second. When estimating complexity, you can consider that copying each character costs around 100 elementary operations.