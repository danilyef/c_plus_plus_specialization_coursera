### Word Splitting 

Write a function called SplitIntoWords that splits a string into words using spaces.

You can be sure that:

The string is not empty.
The string only consists of Latin letters and spaces.
The first and last characters of the string are not spaces.
The string does not contain two consecutive spaces.

```objectivec
vector<string> SplitIntoWords(const string& s);

int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;
  
  return 0;
}

```
