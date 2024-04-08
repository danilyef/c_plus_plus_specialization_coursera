#### Programming Task: "Sentence Splitting"

Write a summary of the task and provide general instructions. If the task involves initial files, add a link to them.

Given a vector of tokens, write a function that splits the tokens into sentences:

```cpp
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens);
```

Where `Token` is a template type, about which only one thing is known: it has a constant method `IsEndSentencePunctuation`, which returns `true` if the token is a punctuation mark ending a sentence, and `false` otherwise. Objects of this type are forbidden to copy. Attempting to copy these objects will result in a compilation error.

`Sentence` is a synonym for the type `vector`, declared as follows:

```cpp
template <typename Token>
using Sentence = vector<Token>;
```

A sentence is considered a sequence of tokens ending with consecutive tokens that are end-of-sentence punctuation marks. In other words, any sentence must consist of two parts:

1. Tokens for which `IsEndSentencePunctuation` returns `false` (such tokens must be present in the sentence except possibly for the first sentence).
2. Tokens for which `IsEndSentencePunctuation` returns `true` (such tokens must be present in the sentence except possibly for the last sentence).

Constraints:
- The maximum number of tokens is \(10^6\).
- The execution time of one function call is limited to 1 second.