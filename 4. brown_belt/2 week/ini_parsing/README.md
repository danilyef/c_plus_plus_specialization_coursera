### Programming Task: Library for Working with INI Files

In the lectures, we developed libraries for loading data from XML and JSON formats, placing each of them in its own namespace. In this task, you need to do the same for the INI format. You need to develop a library with the following interface:

```cpp
using Section = unordered_map<string, string>;

class Document {
public:
  Section& AddSection(string name);
  const Section& GetSection(const string& name) const;
  size_t SectionCount() const;

private:
  unordered_map<string, Section> sections;
};

Document Load(istream& input);
```

**Requirements:**

- The contents of the library should be in the `Ini` namespace.
- The interface shown above should be declared in the file `ini.h`.
- Submit an archive with the full implementation of the library for review; the archive should include the file `ini.h`.

During testing, the `Load` function will be given text in the format:

```
[section 1]
key1=value1
key2=value2

[section 2]
key3=value3
key4=value4
```

It is guaranteed that our tests will use only valid INI files, meaning strings in the format `key=value` will always be inside some section and contain exactly one `=` character. A line in the INI file is either empty or does not contain leading spaces.