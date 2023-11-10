#### Programming Task: Bus Stops - 2 ####

In this problem, you need to assign numbers to bus routes.

Namely, for each route given by a set of stop names, you need to either return a new number (1 for the first route, 2 for the second, and so on), or return the number of an existing route to which such a set of stops corresponds.

Sets of stops obtained from each other by a permutation of stops are considered different (see example).

##### Note #####
In C++, a dictionary key can be not only a number or a string, but also another container, such as *vector*.

##### Input format #####
First enter the number of requests *Q*, then *Q* descriptions of requests.

Each request is a positive number of stops *N* followed by space-separated *N* different stop names for the corresponding route. Stop names consist only of Latin letters and underscores.

##### Output format #####
Print the answer to each query on a separate line.

If a route with this set of stops already exists, print **Already exists for *i***, where ***i*** is the number of the route with this set of stops. Otherwise, allocate a new number ***i*** to the entered set of stops and output it in the format **New bus *i***.

##### Example #####
###### Input ######
```objectivec
4
2 Marushkino Kokoshkino
1 Kokoshkino
2 Marushkino Kokoshkino
2 Kokoshkino Marushkino
```

###### Output ######
```objectivec
New bus 1
New bus 2
Already exists for 1
New bus 3
```

