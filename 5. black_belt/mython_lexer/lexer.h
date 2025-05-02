#pragma once

#include <iosfwd>
#include <string>
#include <sstream>
#include <variant>
#include <stdexcept>
#include <optional>

class TestRunner;

namespace Parse {

namespace TokenType {
  struct Number {
    int value;
  };

  struct Id {
    std::string value;
  };

  struct Char {
    char value;
  };

  struct String {
    std::string value;
  };

  struct Class{};
  struct Return{};
  struct If {};
  struct Else {};
  struct Def {};
  struct Newline {};
  struct Print {};
  struct Indent {};
  struct Dedent {};
  struct Eof {};
  struct And {};
  struct Or {};
  struct Not {};
  struct Eq {};
  struct NotEq {};
  struct LessOrEq {};
  struct GreaterOrEq {};
  struct None {};
  struct True {};
  struct False {};
}

using TokenBase = std::variant<
  TokenType::Number,
  TokenType::Id,
  TokenType::Char,
  TokenType::String,
  TokenType::Class,
  TokenType::Return,
  TokenType::If,
  TokenType::Else,
  TokenType::Def,
  TokenType::Newline,
  TokenType::Print,
  TokenType::Indent,
  TokenType::Dedent,
  TokenType::And,
  TokenType::Or,
  TokenType::Not,
  TokenType::Eq,
  TokenType::NotEq,
  TokenType::LessOrEq,
  TokenType::GreaterOrEq,
  TokenType::None,
  TokenType::True,
  TokenType::False,
  TokenType::Eof
>;



struct Token : TokenBase {
  using TokenBase::TokenBase;

  template <typename T>
  bool Is() const {
    return std::holds_alternative<T>(*this);
  }

  template <typename T>
  const T& As() const {
    return std::get<T>(*this);
  }

  template <typename T>
  const T* TryAs() const {
    return std::get_if<T>(this);
  }
};

bool operator == (const Token& lhs, const Token& rhs);
std::ostream& operator << (std::ostream& os, const Token& rhs);

class LexerError : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

enum class ReturnTokenType {
  ReturnToken,   // previously "return true"
  NoToken,       // previously "return false"
  Continue       // for cases where we need to continue parsing
};

class Lexer {
public:
  explicit Lexer(std::istream& input);

  const Token& CurrentToken() const;
  Token NextToken();

  template <typename T>
  const T& Expect() const {
    if(!CurrentToken().Is<T>()) {
      throw LexerError("Error");
    }
    return CurrentToken().As<T>();
  }

  template <typename T, typename U>
  void Expect(const U& value) const {
    if(!CurrentToken().Is<T>()) {
      throw LexerError("Error");
    }
    if(CurrentToken().As<T>().value != value) {
      throw LexerError("Error");
    }
  }

  template <typename T>
  const T& ExpectNext() {
    NextToken();
    const T& token = Expect<T>();
    return token;
  }

  template <typename T, typename U>
  void ExpectNext(const U& value) {
    NextToken();
    Expect<T, U>(value);
  }

private:
  bool HandleEOF();
  ReturnTokenType HandleNewline(char ch);
  ReturnTokenType HandleIndent(char ch, char next);
  ReturnTokenType HandleStrings(char ch, char next, std::string& value, bool& is_string, char& string_quote);
  void NumbersValuesAdd(char ch, std::string& value, int& number_value);
  bool HandleKeywords(const std::string& value);
  bool HandleComparisons(const std::string& value);
  bool HandleSymbols(char ch, char next);
  bool HandleNumbers(char next, const std::string& value, int number_value);
  bool HandleIDs(char ch, char next, const std::string& value);

  std::istream& input_;
  Token current_token;  
  std::string current_line;
  size_t current_indent_level = 0;
  size_t cursor_position = 0;
};

void RunLexerTests(TestRunner& test_runner);

} /* namespace Parse */
