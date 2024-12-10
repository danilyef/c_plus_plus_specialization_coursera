### Programming Task: "UPDATE_FIELD" Macro

Let's continue working on the AviaScanner flight search service. Our service stores a database of tickets in the form of a `vector<AirlineTicket>`, where `AirlineTicket` is the same structure as in the previous task. Periodically, our service visits airline websites, collects fresh information about available tickets, and updates records in its database. This is done using the `void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates)` function. The `updates` parameter contains pairs (field name, new value), including only the fields that have changed. Here is an example of how the `UpdateTicket` function works:

```cpp
void UpdateTicketExample() {
  AirlineTicket t;
  t.price = 5000;
  t.from = "DME";
  t.to = "AER";

  const map<string, string> updates = {
    {"price", "3500"},
    {"from", "VKO"}
  };
  UpdateTicket(t, updates);
  ASSERT_EQUAL(t.from, "VKO");
  ASSERT_EQUAL(t.to, "AER");
  ASSERT_EQUAL(t.price, 3500);
}
```

The `UpdateTicket` function could be implemented as follows:

```cpp
void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates) {
  map<string, string>::const_iterator it;

  it = updates.find("to");
  if (it != updates.end()) {
    ticket.to = it->second;
  }

  it = updates.find("from");
  if (it != updates.end()) {
    ticket.from = it->second;
  }

  it = updates.find("price");
  if (it != updates.end()) {
    istringstream is(it->second);
    is >> ticket.price;
  }

  // ...
}
```

However, there is code duplication here, and it can be simplified using a macro. The task is to write a macro called `UPDATE_FIELD` to simplify the `UpdateTicket` function:

```cpp
#define UPDATE_FIELD(ticket, field, values) ...

void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates) {
  UPDATE_FIELD(ticket, to, updates);
  UPDATE_FIELD(ticket, from, updates);
  UPDATE_FIELD(ticket, price, updates);
  UPDATE_FIELD(ticket, airline, updates);
  // ...
}
```

Please write the `UPDATE_FIELD` macro. You are given a file `airline_ticket.h`, containing declarations for the `Time`, `Date`, and `AirlineTicket` structures, as well as a solution template in the form of a cpp file named `update_field.cpp`. Submit the cpp file for review, which should:

- Include the `airline_ticket.h` header.
- Contain the `UPDATE_FIELD` macro.
- Include definitions for operators needed to read the `Date` and `Time` classes from the `istream` and their use in the `ASSERT_EQUAL` macro (refer to the input format in the unit tests in the `update_field.cpp` file).
