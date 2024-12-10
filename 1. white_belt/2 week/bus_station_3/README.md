### Programming Task: Bus Stops - 3 

In this problem, you need to assign numbers to bus routes.

Namely, for each route given by a set of stop names, you must either return a new number (1 for the first route, 2 for the second, and so on), or return the number of an existing route that corresponds to such a set of stops.

In contrast to the "Bus stops - 2" problem, the sets of stops that can be obtained from each other by rearranging elements or adding/removing duplicates should be considered the same.

### Input format 
First enter the number of requests *Q*, then *Q* descriptions of requests.

Each request is a positive number of stops *N* followed by space-separated *N* names of the corresponding route's stops (not necessarily different). Stop names consist only of Latin letters and underscores.

### Output format 
Print the answer to each query on a separate line.

If a route with this set of stops already exists, print **Already exists for *i***, where ***i*** is the number of the route with this set of stops. Otherwise, allocate a new number ***i*** to the entered set of stops and output it in the format **New bus *i***.

### Example 
**Input**
```objectivec
5
2 Marushkino Kokoshkino
1 Kokoshkino
2 Marushkino Kokoshkino
2 Kokoshkino Marushkino
2 Kokoshkino Kokoshkino
```

**Output**
```objectivec
New bus 1
New bus 2
Already exists for 1
Already exists for 1
Already exists for 2
```
