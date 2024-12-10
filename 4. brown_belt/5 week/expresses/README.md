### Programming Task: Express Routes

You are given a task and its solution, which is correct but does not meet the specified time limits. Refactor this solution and submit it to the system.

**Problem Statement**
Design a simple routing system for express trains that run along a single railway line, represented as a straight line. Your program must handle two types of queries:

1. **ADD start finish** — Add an express route to the system that runs from station `start` to station `finish` and back. The express does not make any intermediate stops. Stations are given as integers, representing their distance from the central station (station 0).
  
2. **GO start finish** — Try to plan a direct route from station `start` to station `finish`. If an express route exists between these two stations, output `0`. Otherwise, output a positive integer — the minimum distance you can get to station `finish`, starting from station `start`, using at most one express route.

**Input Format**
The first line contains the number of queries `Q` — a natural number not exceeding \(10^5\). In the next `Q` lines, queries are given according to the format described above. It is guaranteed that the station numbers are integers and do not exceed \(10^9\) in absolute value.

**Output Format**
For each `GO` query, output a single non-negative integer — the minimum distance to the final station, calculated according to the described rules.

**Constraints**
- The program must handle all queries within 1 second.
- All guarantees described are valid for all test cases. You do not need to verify the correctness of the tests.

**Example**

**Input**
```
7
ADD -2 5
ADD 10 4
ADD 5 8
GO 4 10
GO 4 -2
GO 5 0
GO 5 100
```

**Output**
```
0
6
2
92
```

**Explanation of the Example**
1. In the first `GO` query, it is beneficial to use the express between stations 10 and 4.
2. In the second query, it is better to stay in place than to use any express route.
3. In the third and fourth `GO` queries, the express routes `-2 5` and `5 8` are needed to minimize the distance.