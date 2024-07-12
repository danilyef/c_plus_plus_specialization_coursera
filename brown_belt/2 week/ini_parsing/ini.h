#pragma once

#include <istream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <tuple>
#include <iostream>
#include <cctype>
using namespace std;

namespace Ini{
using Section = unordered_map<string, string>;

class Document {
public:
  explicit Document(unordered_map<string,Section> doc);
  Document(){};
  Section& AddSection(string name);
  const Section& GetSection(const string& name) const;
  size_t SectionCount() const;

private:
  unordered_map<string, Section> sections;
};

Document Load(istream& input);

}