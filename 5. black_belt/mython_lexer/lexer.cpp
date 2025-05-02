#include "lexer.h"

#include <algorithm>
#include <charconv>
#include <unordered_map>
#include <iostream>
#include <cmath>

using namespace std;

namespace Parse {

bool operator == (const Token& lhs, const Token& rhs) {
  using namespace TokenType;

  if (lhs.index() != rhs.index()) {
    return false;
  }
  if (lhs.Is<Char>()) {
    return lhs.As<Char>().value == rhs.As<Char>().value;
  } else if (lhs.Is<Number>()) {
    return lhs.As<Number>().value == rhs.As<Number>().value;
  } else if (lhs.Is<String>()) {
    return lhs.As<String>().value == rhs.As<String>().value;
  } else if (lhs.Is<Id>()) {
    return lhs.As<Id>().value == rhs.As<Id>().value;
  } else {
    return true;
  }
}

std::ostream& operator << (std::ostream& os, const Token& rhs) {
  using namespace TokenType;

#define VALUED_OUTPUT(type) \
  if (auto p = rhs.TryAs<type>()) return os << #type << '{' << p->value << '}';

  VALUED_OUTPUT(Number);
  VALUED_OUTPUT(Id);
  VALUED_OUTPUT(String);
  VALUED_OUTPUT(Char);

#undef VALUED_OUTPUT

#define UNVALUED_OUTPUT(type) \
    if (rhs.Is<TokenType::type>()) return os << #type;

  UNVALUED_OUTPUT(Class);
  UNVALUED_OUTPUT(Return);
  UNVALUED_OUTPUT(If);
  UNVALUED_OUTPUT(Else);
  UNVALUED_OUTPUT(Def);
  UNVALUED_OUTPUT(Newline);
  UNVALUED_OUTPUT(Print);
  UNVALUED_OUTPUT(Indent);
  UNVALUED_OUTPUT(Dedent);
  UNVALUED_OUTPUT(And);
  UNVALUED_OUTPUT(Or);
  UNVALUED_OUTPUT(Not);
  UNVALUED_OUTPUT(Eq);
  UNVALUED_OUTPUT(NotEq);
  UNVALUED_OUTPUT(LessOrEq);
  UNVALUED_OUTPUT(GreaterOrEq);
  UNVALUED_OUTPUT(None);
  UNVALUED_OUTPUT(True);
  UNVALUED_OUTPUT(False);
  UNVALUED_OUTPUT(Eof);

#undef UNVALUED_OUTPUT

  return os << "Unknown token :(";
}


const std::unordered_map<std::string, Token>key_words_mapping = {
  {"class", TokenType::Class{}},
  {"return", TokenType::Return{}},
  {"if", TokenType::If{}},
  {"else", TokenType::Else{}},
  {"def", TokenType::Def{}},
  {"print", TokenType::Print{}},
  {"or", TokenType::Or{}},
  {"and", TokenType::And{}},
  {"not", TokenType::Not{}},
  {"True", TokenType::True{}},
  {"False", TokenType::False{}},
  {"None", TokenType::None{}},
  {"self", TokenType::Id{"self"}},
  {"__init__", TokenType::Id{"__init__"}},
  {"__str__", TokenType::Id{"__str__"}},
  {"__repr__", TokenType::Id{"__repr__"}},
  {"__eq__", TokenType::Id{"__eq__"}},
  {"__ne__", TokenType::Id{"__ne__"}},
  {"__lt__", TokenType::Id{"__lt__"}},
  {"__gt__", TokenType::Id{"__gt__"}},
  {"__le__", TokenType::Id{"__le__"}},
  {"__ge__", TokenType::Id{"__ge__"}},
  {"__add__", TokenType::Id{"__add__"}},
  {"__sub__", TokenType::Id{"__sub__"}},
};

const std::unordered_map<std::string, Token> comparisons_mapping = {
  {"==", TokenType::Eq{}},
  {">=", TokenType::GreaterOrEq{}},
  {"<=", TokenType::LessOrEq{}},
  {"!=", TokenType::NotEq{}}
};

const std::unordered_map<char, Token> symbols_mapping = {
  {'=', TokenType::Char{'='}},
  {'-', TokenType::Char{'-'}},
  {'+', TokenType::Char{'+'}},
  {'*', TokenType::Char{'*'}},
  {'/', TokenType::Char{'/'}},
  {',', TokenType::Char{','}},
  {'.', TokenType::Char{'.'}},
  {':', TokenType::Char{':'}},
  {'(', TokenType::Char{'('}},
  {')', TokenType::Char{')'}},
  {'<', TokenType::Char{'<'}},
  {'>', TokenType::Char{'>'}},
  {'?', TokenType::Char{'?'}},
  {'!', TokenType::Char{'!'}},
  {'#', TokenType::Char{'#'}}
};


Lexer::Lexer(std::istream& input) : input_(input) {
  NextToken();
};

const Token& Lexer::CurrentToken() const {
  return current_token;
}

bool Lexer::HandleEOF() {
  if (input_.eof()) {
    if (!current_line.empty() && !(current_token == TokenType::Newline{})) {
      current_line.clear();
      current_token = TokenType::Newline{};
      return true;
    }
    current_token = TokenType::Eof{};
    return true;
  }
  return false;
}

ReturnTokenType Lexer::HandleNewline(char ch) {
  if (ch != '\n') {
    current_line += ch;
    return ReturnTokenType::NoToken;
  }
  
  if (input_.peek() == EOF && current_indent_level > 0) {
    current_token = TokenType::Dedent{};
    return ReturnTokenType::ReturnToken;
  }

  bool is_empty_line = current_line.find_first_not_of(" \t\r") == std::string::npos;
  if (is_empty_line) {
    current_line.clear();
    return ReturnTokenType::Continue;
  }
  
  current_line.clear();
  current_token = TokenType::Newline{};
  cursor_position = 0;
  return ReturnTokenType::ReturnToken;
}

ReturnTokenType Lexer::HandleIndent(char ch, char next) {
  // Calculate dedent levels
  int dedent_levels = (current_indent_level - cursor_position) / 2;
  bool is_after_newline = (current_token == TokenType::Newline{});
  bool is_after_dedent = (current_token == TokenType::Dedent{});
  
  // Case 1: Continue dedenting if needed
  if (is_after_dedent && ch != ' ' && dedent_levels > 0) {
    input_.putback(ch);
    current_indent_level -= 2;
    current_token = TokenType::Dedent{};
    return ReturnTokenType::ReturnToken;
  }
  
  // Case 2: Handle spaces after newline (potential indentation)
  if (is_after_newline && ch == ' ') {
    cursor_position++;
    
    // At non-space after spaces, decide if indent/dedent is needed
    if (next != ' ' && cursor_position > current_indent_level) {
        // Indentation increased
        current_indent_level += 2;
        current_token = TokenType::Indent{};
        return ReturnTokenType::ReturnToken;
    } else if (next != ' ' && cursor_position < current_indent_level) {
      // Indentation decreased
      current_indent_level -= 2;
      current_token = TokenType::Dedent{};
      return ReturnTokenType::ReturnToken;
    }

    // Continue processing spaces
    return ReturnTokenType::Continue;
  }
  
  // Case 3: Non-space after newline with less indentation
  if (is_after_newline && ch != ' ' && cursor_position < current_indent_level) {
    input_.putback(ch);
    current_indent_level -= 2;
    current_token = TokenType::Dedent{};
    return ReturnTokenType::ReturnToken;
  }
  
  // Default case: Not related to indentation
  cursor_position++;
  return ReturnTokenType::NoToken;
}

ReturnTokenType Lexer::HandleStrings(char ch, char next, std::string& value, bool& is_string, char& string_quote) {
  if ((ch == '"' || ch == '\'') && !is_string) {
    is_string = true;
    string_quote = ch;
    value.clear();
    return ReturnTokenType::Continue;
  }
  
  if ((ch == string_quote) && is_string) {
    is_string = false;
    current_token = TokenType::String{value};
    return ReturnTokenType::ReturnToken;
  }
  
  if (is_string) {
    value += ch;
    return ReturnTokenType::Continue;
  }
  
  return ReturnTokenType::NoToken;
}

void Lexer::NumbersValuesAdd(char ch, std::string& value, int& number_value) {
  if (isdigit(ch) && value.empty()) {
    number_value = number_value * 10 + (ch - '0');
  } else {
    value += ch;
  }
}

bool Lexer::HandleKeywords(const std::string& value) {
  if (key_words_mapping.count(value) > 0) {
    current_token = key_words_mapping.at(value);
    return true;
  }
  return false;
}

bool Lexer::HandleComparisons(const std::string& value) {
  if (comparisons_mapping.count(value) > 0) {
    current_token = comparisons_mapping.at(value);
    return true;
  }
  return false;
}

bool Lexer::HandleSymbols(char ch, char next) {
  if (symbols_mapping.count(ch) > 0 && comparisons_mapping.count(std::string({ch, next})) == 0) {
    current_token = symbols_mapping.at(ch);
    return true;
  }
  return false;
}

bool Lexer::HandleNumbers(char next, const std::string& value, int number_value) {
  // Common token boundary check
  bool is_boundary = isspace(next) || next == EOF;
  
  // Handle number tokens
  bool is_delimited_by_token = current_token == TokenType::Char{'('} || 
                              current_token == TokenType::Char{','};
  
  if ((is_boundary || is_delimited_by_token) && value.empty()) {
    current_token = TokenType::Number{number_value};
    return true;
  }
  
  return false;
}

bool Lexer::HandleIDs(char ch, char next, const std::string& value) {
  // Common token boundary check
  bool is_boundary = isspace(next) || next == EOF;
  
  // Handle identifier tokens
  bool is_not_symbol = symbols_mapping.count(ch) == 0;
  bool is_symbol_boundary = symbols_mapping.count(next) > 0;
  
  if (is_not_symbol && (is_boundary || is_symbol_boundary)) {
    current_token = TokenType::Id{value};
    return true;
  }
  
  return false;
}

Token Lexer::NextToken() {
  char ch;
  std::string value;
  int number_value = 0;
  bool is_string = false; 
  char string_quote;

  // Handle EOF
  if (HandleEOF()) {
    return current_token;
  }
  
  while (input_.get(ch)) {
    char next = input_.peek();
    // Handle newlines
    ReturnTokenType newlineResult = HandleNewline(ch);
    if (newlineResult == ReturnTokenType::ReturnToken) {
      return current_token;
    } else if (newlineResult == ReturnTokenType::Continue) {
      continue;
    }
    
    // Handle indentation
    ReturnTokenType indentResult = HandleIndent(ch, next);
    if (indentResult == ReturnTokenType::ReturnToken) {
      return current_token;
    } else if (indentResult == ReturnTokenType::Continue) {
      continue;
    }

    // Skip spaces (except in strings)
    if (ch == ' ' && !is_string) {
      continue;
    }
        
    // Handle strings
    ReturnTokenType stringResult = HandleStrings(ch, next, value, is_string, string_quote);
    if (stringResult == ReturnTokenType::ReturnToken) {
      return current_token;
    } else if (stringResult == ReturnTokenType::Continue) {
      continue;
    }

    // Process digits and collect values
    NumbersValuesAdd(ch, value, number_value);

    // Check for keywords
    if (HandleKeywords(value)) {
      return current_token;
    }

    // Check for comparison operators
    if (HandleComparisons(value)) {
      return current_token;
    }

    // Check for symbols
    if (HandleSymbols(ch, next)) {
      return current_token;
    }

    // Handle numbers
    if (HandleNumbers(next, value, number_value)) {
      return current_token;
    }

    // Handle identifiers
    if (HandleIDs(ch, next, value)) {
      return current_token;
    }
  } 

  // End of file
  current_token = TokenType::Eof{};
  return current_token;
}

} /* namespace Parse */