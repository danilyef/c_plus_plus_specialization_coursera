#include "ini.h"


namespace Ini {
using Section = unordered_map<string, string>;


Document::Document(unordered_map<string,Section> doc) : sections(std::move(doc)) {};

Section& Document::AddSection(string name){
  if(sections.find(name) == sections.end()){
     Section& section = sections[std::move(name)] = Section();
     return section;
  }
  Section& section = sections.at(std::move(name));
  return section;
};

const Section& Document::GetSection(const string& name) const {
  if (sections.find(name) == sections.end()) {
      throw std::out_of_range("unknown section");
    }
    return sections.at(name);
};

size_t Document::SectionCount() const {
    return sections.size();
};


 Document Load(istream &input) {
        Document result;

        Section *current_section = nullptr;
        for (string line; getline(input, line);) {
            if (!line.empty()) {
                if (line[0] == '[') {
                    current_section = &result.AddSection(line.substr(1, line.size() - 2));
                } else {
                    size_t eq_pos = line.find('=');
                    current_section->insert({line.substr(0, eq_pos), line.substr(eq_pos + 1)});
                }
            }
        }

        return result;
    }


}



