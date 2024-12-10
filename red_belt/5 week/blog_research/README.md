### Programming Assignment: Blog Research

The major IT company Yangle is conducting research on the mention of its brand in blogs and social networks. The company's analysts have already extracted the publications of interest and formed a set of keywords. They are interested in how many times each keyword appears in the set of publications.

Help them do this — write a function `Stats ExploreKeyWords(const set<string>& key_words, istream& input)`. Its parameters are:

- `key_words` — a set of keywords
- `input` — the input stream containing the publications to be examined in blogs and social networks, where one line represents one publication.

The function `ExploreKeyWords` should return a structure `Stats`, which stores how many times each word from `key_words` has appeared in the `input` stream:

```cpp
struct Stats {
  map<string, int> word_frequencies;

  void operator += (const Stats& other);
};
```

When counting occurrences of keywords in the text, only occurrences as separate words should be considered. Words are separated from each other by one or more spaces. For example, let's assume that `key_words = {"yangle", "rocks", "sucks", "all"}` and we have a publication from the social network Switter: "Goondex really sucks, but yangle rocks ! Use yangle". The word "yangle" appears in it twice, "rocks" once, and the words "all" and "sucks" do not appear at all. The word "sucks" does not appear at all because in this example it is a prefix of the word "sucks," (according to the condition, words are separated only by spaces). Despite the fact that the word "all" is part of the word "really," its occurrence cannot be counted, as it is not a separate word.

To meet the Time Limit, think about whether this task can be parallelized.

Note
Before this, in lectures, we showed how to use the `async` function to asynchronously launch lambda functions without parameters. However, it can also be used to launch functions with parameters. For example,

```cpp
string Join(string s, string t) {
  return s + t;
}

string a = "Hello";
string b = " world";
future<int> f = async(Join, a, b);
```

As you can see, to pass parameters to a function asynchronously launched, they need to be specified as parameters of the `async` function after the function itself. It is important to note that when called in this way, copies of the actual parameters will be created (i.e., in our example above, strings `a` and `b` will be copied). This is not always desirable. For example, if we have a constant object that threads only read, we do not need to create a copy of it, and we can pass it by reference. To do this, use the `ref` function from the `<functional>` header file.