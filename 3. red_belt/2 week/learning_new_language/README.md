### Programming task: Learning a new language.

The student was asked to write a class called Learner to assist in learning a foreign language. The class's public interface should have two functions:

```cpp
int Learn(const vector<string>& words);
vector<string> KnownWords();
```

The Learn function should take a batch of words, "memorize" them, and return the count of different new words. The KnownWords function should return a sorted list of all learned words in alphabetical order. The list should not contain duplicates.

The student provided the following solution to the task, but it seems to be working very slowly. Your task is to speed it up without changing the public interface of the Learner class.

You have been given a file named `learner.cpp` with the slow solution. Find the bottlenecks in it, correct them, and submit the modified class to the testing system.

Your code will be tested as follows:

```cpp
int main() {
  Learner learner;
  string line;
  while (getline(cin, line)) {
    vector<string> words;
    stringstream ss(line);
    string word;
    while (ss >> word) {
      words.push_back(word);
    }
    cout << learner.Learn(words) << "\n";
  }
  cout << "=== known words ===\n";
  for (auto word : learner.KnownWords()) {
    cout << word << "\n";
  }
}
```