#include "json.h"

using namespace std;

namespace Json {

  Document::Document(Node root) : root(std::move(root)) {
  }

  const Node& Document::GetRoot() const {
    return root;
  }

  Node LoadNode(istream& input);

  Node LoadArray(istream& input) {
    vector<Node> result;

    for (char c; input >> c && c != ']'; ) {
      if (c != ',') {
        input.putback(c);
      }
      result.push_back(LoadNode(input));
    }

    return Node(std::move(result));
  }


  Node LoadBool(istream& input) {
    string value(5, '\0');

    for (int i = 0; i < 4; ++i) {
      input >> value[i];
    }

    if (value.substr(0, 4) == "true") {
      return Node(true);
    }

    input >> value[4];
    return Node(false);
  }


Node LoadNumber(std::istream& input) {
    int result = 0;

    int sign = 1;
    if (input.peek() == '-') {
      input.ignore();
      sign = -1;
    }

    while (isdigit(input.peek())) {
        int digit = input.get() - '0';
        result *= 10;
        result += digit;
    }

    if (input.peek() != '.') {
      return Node(sign * result);
    }

    input.ignore();
    double double_res = result;
    double factor = 0.1;
    while (isdigit(input.peek())) {
        int digit = input.get() - '0';
        double_res += digit * factor;
        factor *= 0.1;
    }
    return Node(sign * double_res);
}

  
  Node LoadString(istream& input) {
    string line;
    getline(input, line, '"');
    return Node(std::move(line));
  }

  Node LoadDict(istream& input) {
    map<string, Node> result;

    for (char c; input >> c && c != '}'; ) {
      if (c == ',') {
        input >> c;
      }

      string key = LoadString(input).AsString();
      input >> c;
      result.emplace(std::move(key), LoadNode(input));
    }

    return Node(std::move(result));
  }

  Node LoadNode(istream& input) {
    char c;
    input >> c;

    if (c == '[') {
      return LoadArray(input);
    } else if (c == '{') {
      return LoadDict(input);
    } else if (c == '"') {
      return LoadString(input);
    } else if (c == 't' || c == 'f') {
      input.putback(c);
      return LoadBool(input);
    } else {
      input.putback(c);
      return LoadNumber(input);
    }
  }

  void PrintNode(const Node& node, std::ostream& os) {
      if (node.is<std::string>()) {
        PrintString(node.AsString(), os);
      } else if (node.is<int>()) {
        PrintInt(node.AsInt(), os);
      } else if (node.is<double>()) {
        PrintDouble(node.AsDouble(), os);
      } else if (node.is<bool>()) {
        os << (node.AsBool() ? "true" : "false");
      } else if (node.is<std::vector<Node>>()) {
        PrintArray(node.AsArray(), os);
      } else if (node.is<std::map<std::string, Node>>()) {
        PrintDict(node.AsMap(), os);
      } else {
        os << "null";
      }
  }

  void PrintInt(const int num , std::ostream& os){
    os << num;
  };
  void PrintDouble(const double num , std::ostream& os){
    os << num;
  };
  void PrintString(const std::string& str, std::ostream& os){
    os << '"' << str << '"'; 
  };
  
  void PrintArray(const std::vector<Node>& arr, std::ostream& os){
    os << '[';
    for (auto it = arr.begin(); it != arr.end(); ++it){
      PrintNode(*it,os);
      if (std::next(it) != arr.end()) {  
        os << ", ";
      }
    } 
    os << ']' ;

  };
  void PrintDict(const std::map<std::string, Node>& dict, std::ostream& os) {
    os << '{';
    for (auto it = dict.begin(); it != dict.end(); ++it) {
        PrintString(it->first, os);
        os << ": ";
        PrintNode(it->second, os); 
        if (std::next(it) != dict.end()) {  
            os << ", ";
        }
    }
    os << '}';
}


  Document Load(istream& input) {
    return Document{LoadNode(input)};
  }

}
