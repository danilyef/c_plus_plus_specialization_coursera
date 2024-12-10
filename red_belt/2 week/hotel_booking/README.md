### Programming Task: Hotel Reservation System

### Condition:
Develop a hotel reservation system that allows clients to book rooms and owners to monitor demand. Your program should process the following events:

- BOOK time hotel_name client_id room_count — reserve client_id room_count rooms at hotel_name at the time specified by time. Time is measured in seconds from some point.

- CLIENTS hotel_name — output the number of different clients who booked rooms at hotel_name in the last 24 hours. More formally, the time range of interest is described as follows: let current_time be the time of the last BOOK event, then in this query, consider all events with current_time − 86400 < time ⩽ current_time, where 86400 is the number of seconds in a day. Note that the last reservation should be included, and a reservation exactly 24 hours before it should not be considered.

- ROOMS hotel_name — output the number of rooms booked in hotel_name in the last 24 hours.

### Input Format:
The first line contains the number of queries Q — a natural number not exceeding 10^5. The next Q lines, following the format described above, input the queries. It is guaranteed that:

- time is an integer ranging from −10^18 to 10^18 and does not decrease from event to event.

- hotel_name is a string of Latin letters and numbers, with a length not exceeding 12 characters.

- client_id is a natural number not exceeding 10^9.

- room_count is a positive integer not exceeding 1000.

### Output Format:
For each CLIENTS and ROOMS query, output a single integer — the answer to the query. If the specified hotel has not had any bookings according to the query, output 0.

### Constraints:
1 second to execute all queries.

### Example:

**Input:**
```
11
CLIENTS Marriott
ROOMS Marriott
BOOK 10 FourSeasons 1 2
BOOK 10 Marriott 1 1
BOOK 86409 FourSeasons 2 1
CLIENTS FourSeasons
ROOMS FourSeasons
CLIENTS Marriott
BOOK 86410 Marriott 2 10
ROOMS FourSeasons
ROOMS Marriott
```

**Output:**
```
0
0
2
3
1
1
10
```