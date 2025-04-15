#pragma once

#include "iterator_range.h"
#include "contact.pb.h"

#include <optional>
#include <string>
#include <string_view>
#include <vector>
#include <set>
#include <iosfwd>


struct Date {
  int year, month, day;
  
  Date(int y, int m, int d) : year(y), month(m), day(d) {}
};

struct Contact {
  std::string name;
  std::optional<Date> birthday;
  std::vector<std::string> phones;

  bool operator<(const Contact& other) const {
    return name < other.name;
  }
};

class CompareContacts {
public:
    CompareContacts(std::string_view name_prefix) : prefix_size(name_prefix.size()) {}
    CompareContacts(size_t prefix_size) : prefix_size(prefix_size) {}
    bool operator()(const Contact& lhs, const Contact& rhs) const {
        return lhs.name.substr(0, prefix_size) < rhs.name.substr(0, prefix_size);
    }
private:
  size_t prefix_size;
};



class PhoneBook {
public:
  using SortedContacts = std::vector<Contact>;
  using SortedContactsIt = SortedContacts::const_iterator;
  using ContactRange = IteratorRange<SortedContactsIt>;
  
  explicit PhoneBook(std::vector<Contact> contacts);

  ContactRange FindByNamePrefix(std::string_view name_prefix) const;

  void SaveTo(std::ostream& output) const;

private:
  std::vector<Contact> contact_book;

};

PhoneBook DeserializePhoneBook(std::istream& input);

