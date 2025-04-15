### **Programming task: Phone Book**

In this task, we will develop a `PhoneBook` class that performs a subset of the tasks of a mobile phone's address book. Our class will solve three tasks:

1. Serialization of contacts to an output stream (for example, to save them in the phone's memory or to send them to a contact synchronization server).
2. Deserialization of contacts from an input stream.
3. Searching for contacts whose names start with a given string — this function is useful when a user types a name, and the address book shows all contacts whose names begin with the entered string.

A contact in our address book can have the following characteristics:

- Name
- Date of birth
- Phone numbers

The name is always present (though it may be empty), the date of birth may be missing, and there may be zero or more phone numbers. Thus, we handle different usage scenarios for the phone book:

- Recording someone's birthday to not forget it (name and birthday are present, no phone numbers).
- Storing multiple phone numbers of an acquaintance (name is present, one or more phone numbers, no date of birth).
- Collecting all information about a person in one place (name, birthday, one or more phone numbers).
- Having several phone numbers with an empty name and no date of birth (for example, when the user is training their memory).

Therefore, we can represent a contact in the address book as a structure:

```cpp
struct Date {
  int year, month, day;
};

struct Contact {
  std::string name;
  std::optional<Date> birthday;
  std::vector<std::string> phones;
};
```

The interface of the `PhoneBook` class will look like this:

```cpp
class PhoneBook {
public:
  explicit PhoneBook(std::vector<Contact> contacts);

  IteratorRange<???> FindByNamePrefix(std::string_view name_prefix) const;
  void SaveTo(std::ostream& output) const;
};

PhoneBook DeserializePhoneBook(std::istream& input);
```

For serialization/deserialization, the `PhoneBook` class should use Protobuf. You need to design the proto schema yourself, taking the following requirements into account:

- The proto schema should be in the `PhoneBookSerialize` namespace.
- It must contain a `Contact` message used for serializing a single contact.
- It must contain a `ContactList` message, which includes a `repeated` field of type `Contact`.

The `FindByNamePrefix` method should return a range of all contacts whose names begin with the string `name_prefix`, sorted lexicographically. If `name_prefix` is an empty string, the method should return a range that contains all the contacts in the address book, including those with an empty name. The `FindByNamePrefix` method should work faster than O(N), where N is the number of contacts in the address book.

Submit an archive containing the files `phone_book.h`, `phone_book.cpp`, and `contact.proto`, as well as any other files required to successfully build your project.

### How your code will be tested
Your code will be tested similarly to the unit tests provided in the `main.cpp` file (see below):

- We will check that the `SaveTo` method correctly saves contacts to your designed proto schema.
- We will check that the `DeserializePhoneBook` function loads the address book from the `ContactList` proto message.
- We will check that the `FindByNamePrefix` method works correctly for the deserialized address book.
- We will check the performance of the `FindByNamePrefix` method.