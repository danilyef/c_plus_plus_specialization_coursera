#pragma once

#include <istream>
#include <map>
#include <string>
#include <variant>
#include <vector>
#include <iostream>
#include <sstream>
#include <cctype>
#include <iomanip>


namespace Json {

  class Node : std::variant<std::vector<Node>,
                            std::map<std::string, Node>,
                            int,
                            size_t,
                            std::string,
                            double,
                            bool> {
  public:
    using variant::variant;

    const auto& AsArray() const {
        return std::get<std::vector<Node>>(*this);
    }
    const auto& AsMap() const {
        return std::get<std::map<std::string, Node>>(*this);
    }

    int AsInt() const {
        return std::get<int>(*this);
    }
  
    double AsDouble() const {
        return std::holds_alternative<double>(*this) ? std::get<double>(*this) : std::get<int>(*this);
    }
  
    const auto& AsString() const {
        return std::get<std::string>(*this);
    }

    bool AsBool() const {
      return std::get<bool>(*this);
    }

    template <typename T>
    bool is() const {
      return std::holds_alternative<T>(*this);
    }
  };

  class Document {
  public:
    explicit Document(Node root);

    const Node& GetRoot() const;

  private:
    Node root;
  };

  Document Load(std::istream& input);

  void PrintInt(const int num , std::ostream& os);
  void PrintDouble(const double num , std::ostream& os);
  void PrintString(const std::string& str, std::ostream& os);
  void PrintArray(const std::vector<Node>& arr, std::ostream& os);
  void PrintDict(const std::map<std::string, Node>& dict, std::ostream& os);
  void PrintNode(const Node& node, std::ostream& os);
}


