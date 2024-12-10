### Programming Task: Comparator Generator

Let's imagine that you are developing an innovative flight ticket search service called AviaScanner. In your service, an airline ticket is represented as a structure:

```cpp
struct Date {
  int year, month, day;
};

struct Time {
  int hours, minutes;
};

struct AirlineTicket {
  string from;
  string to;
  string airline;
  Date departure_date;
  Time departure_time;
  Date arrival_date;
  Time arrival_time;
  uint64_t price;
};
```

Currently, you are working on the sorting function for search results. The user enters their query and receives a list of suitable tickets. Then, they can specify sorting parameters for this list, such as sorting by price first, then by departure time, and finally by arrival airport.

To implement sorting as shown in the example, you can use the radix sort algorithm:

```cpp
void SortTickets(vector<AirlineTicket>& tixs) {
  stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
    return lhs.to < rhs.to;
  });
  stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
    return lhs.departure_time < rhs.departure_time;
  });
  stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
    return lhs.price < rhs.price;
  });
}
```

As you can see in the example above, there is code duplication – we had to write three lambda functions that differ only in the field by which sorting is performed. This duplication can be eliminated by writing a macro, SORT_BY, and applying it as follows:

```cpp
void SortTickets(vector<AirlineTicket>& tixs) {
  stable_sort(begin(tixs), end(tixs), SORT_BY(to));
  stable_sort(begin(tixs), end(tixs), SORT_BY(departure_time));
  stable_sort(begin(tixs), end(tixs), SORT_BY(price));
}
```

Write the SORT_BY macro, which takes the name of the AirlineTicket structure field as a parameter. The call `sort(begin(tixs), end(tixs), SORT_BY(some_field))` should result in sorting the tixs vector by the some_field field.