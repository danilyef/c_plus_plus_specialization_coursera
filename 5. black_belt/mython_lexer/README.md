
### **Programming Assignment: Lexical Analyzer for the Mython Language**

In this task, we will develop a lexical analyzer for parsing a program written in the *Mython* language. Let’s look at an example program that checks whether two numbers are coprime:

```python
class GCD:
  def calc(a, b):
    if a == 0 or b == 0:
      return a + b
    else:
      if a < b:
        return self.calc(b, a)
      else:
        return self.calc(b, a - b)

  def is_coprime(a, b):
    return self.calc(a, b) == 1

coprime = False

gcd = None
gcd = GCD()

x = 4
y = 13
coprime = gcd.is_coprime(x, y)
if coprime:
  print x, 'and', y, 'are coprime'
else:
  print x, 'and', y, 'are not coprime'
```

Looking at this, we can identify the following *lexemes* in the Mython language:

* **Keywords**: `class`, `return`, `if`, `else`, `def`, `print`, `or`, `None`, as well as logical operations not shown in this example like `and`, `not`, and logical constants `True`, `False`
* **Integers**
* **Identifiers** (e.g., `GCD`, `calc`, `coprime`, etc.)
* **String literals** (e.g., `'are coprime'`)
* **Multi-character comparison operators** (`==`, `>=`, `<=`, `!=`)
* **Single-character symbols** (`=`, `.`, `,`, `(`, `+`, `<`, etc.)
* **Special lexemes** not visible in the code: "newline", "indent", "dedent", "end of file"

Some lexemes have associated values (e.g., an integer token has a specific numeric value), while others do not (e.g., the `return` keyword or a newline). Each lexeme always belongs to one of the defined types. Therefore, in C++, it’s convenient to represent a lexeme using a `std::variant` type:

```cpp
namespace TokenType {
  struct Number {     // Lexeme for an integer
    int value;
  };

  struct Id {         // Lexeme for an identifier
    std::string value;
  };

  struct Class {};    // Lexeme for 'class'
  struct Return {};   // Lexeme for 'return'
  struct Indent {};   // Lexeme for 'indent'
  struct Dedent {};   // Lexeme for 'dedent'
  struct Eof {};      // Lexeme for end of file
  ...
}

using Token = std::variant<
  TokenType::Number,
  TokenType::Id,
  TokenType::Class,
  TokenType::Return,
  TokenType::Indent,
  TokenType::Dedent,
  ...
  TokenType::Eof
>;
```

This representation is convenient because you can access the `value` field only for lexemes where it makes sense.

---

### Your Task

Implement a class `Lexer` that takes an input stream (`std::istream`) and produces a sequence of lexemes from a Mython program. The interface of the `Lexer` class is as follows:

```cpp
class Lexer {
public:
  explicit Lexer(std::istream& input);

  const Token& CurrentToken() const;
  Token NextToken();

  template <typename T>
  const T& Expect() const;

  template <typename T, typename U>
  void Expect(const U& value) const;

  template <typename T>
  const T& ExpectNext();

  template <typename T, typename U>
  void ExpectNext(const U& value);
};
```

* `CurrentToken` returns a reference to the most recently read token.
* `NextToken` reads and returns the next token from the input stream. If the stream is empty, it returns a `TokenType::Eof` token. After calling `NextToken`, `CurrentToken` will refer to the newly read token.

**Example:**

```cpp
void LexerExample() {
  istringstream input("class Point:");
  Lexer lexer(input);
  ASSERT(std::hold_alternative<TokenType::Class>(lexer.CurrentToken()));

  auto token = lexer.NextToken();
  ASSERT(std::hold_alternative<TokenType::Id>(token));
  ASSERT(std::hold_alternative<TokenType::Id>(lexer.CurrentToken()));
}
```

During parsing, we often expect a specific lexeme (e.g., after a class name, we expect a colon). If a different lexeme appears, it means the input program is incorrect, and we should signal a parsing error. This can be done using the `Expect*` methods:

* `Expect<T>()` checks that the current token is of type `T`. If not, it throws a `LexerError`.
* `Expect<T>(const U& value)` checks that the current token is of type `T` and has a specific value.
* `ExpectNext` calls `NextToken` first, then performs the corresponding `Expect` check.

**Example:**

```cpp
void ParseClassDefinition(Lexer& lexer) {
  lexer.Expect<TokenType::Class>();
  auto name = lexer.ExpectNext<TokenType::Id>().value;
  lexer.ExpectNext<TokenType::Char>(':');
  ...
}
```

---

### Submission Instructions

You are given the files `lexer.h` and `lexer_test.cpp` with a partial set of unit tests. Submit a `.zip` archive containing `lexer.h` and `lexer.cpp`, which implement the `Lexer` class.

In the next assignment, we will use the `Lexer` class to create an interpreter for the Mython language.

---

### Provided Files

The Lexer unit tests use the macros `ASSERT_THROWS` and `ASSERT_DOESNT_THROW`, which have been added to `test_runner.h` to simplify testing of `Expect*` methods. Therefore, the updated `test_runner.h` is included below.

**Files:**

* `lexer_test`
* `lexer.h`
* `lexer.cpp`
* `test_runner`

---

### Note

During testing, only syntactically valid lexemes will be provided as input — e.g., you will not encounter tokens like `123abc76` or strings with unclosed quotes.

---

Would you like help getting started with the implementation of the `Lexer` class?
