### Programming Task: Bus Stops - 1 

Implement a storage system for bus routes. You need to process the following requests:

* **NEW_BUS *bus stop_count stop1 stop2 ...*** — add a bus route named ***bus*** and ***stop_count*** stops named ***stop1, stop2, ...* **
* **BUSES_FOR_STOP *stop*** - display the names of all bus routes passing through the stop ***stop***.
* **STOPS_FOR_BUS *bus*** — display the names of all stops on the ***bus*** route with a list of buses that you can transfer to at each of the stops.
* **ALL_BUSES** - list all routes with stops.

### Input format 
The first input line contains the number of queries *Q*, then the *Q* lines are followed by descriptions of the queries.

It is guaranteed that all names of routes and stops consist only of Latin letters, numbers and underscores.

For each **NEW_BUS *bus stop_count stop1 stop2 ...*** request, it is guaranteed that there is no ***bus*** route, the number of stops is greater than 0, and that number of names follows the ***stop_count*** number stops, and all the names in each list are different.

### Output format 
For each request except **NEW_BUS**, print the corresponding response to it:

- When prompted for **BUSES_FOR_STOP *stop***, output a space-separated list of buses passing through this stop, in the order in which they were created by the **NEW_BUS** commands. If ***stop*** does not exist, print **No stop**.
- When prompted for **STOPS_FOR_BUS *bus***, print the descriptions of the stops on the ***bus*** route on separate lines in the order in which they were specified in the corresponding **NEW_BUS** command. The description of each ***stop*** should be **Stop *stop: bus1 bus2 ...***, where ***bus1 bus2 ...*** is the list of buses passing through the *** stop stop***, in the order they were created by the **NEW_BUS** commands, except for the original ***bus*** route. If no bus other than ***bus*** passes through the ***stop*** stop, print **no interchange** instead of the list of buses for it. If the route ***bus*** does not exist, print **No bus**.
- When prompted for **ALL_BUSES**, display descriptions of all buses in alphabetical order. The description of each ***bus*** route must be of the form **Bus *bus: stop1 stop2 ...***, where ***stop1 stop2 ...*** is the list of bus stops on ***bus** * in the order they were given in the corresponding **NEW_BUS** command. If there are no buses, print **No buses**.

### Example 
**Input**
```commandline
10
ALL_BUSES
BUSES_FOR_STOP Marushkino
STOPS_FOR_BUS 32K
NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo
NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo
BUSES_FOR_STOP Vnukovo
NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo
NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo
STOPS_FOR_BUS 272
ALL_BUSES
```
**Output**
```commandline
No buses
No stop
No bus
32 32K
Stop Vnukovo: 32 32K 950
Stop Moskovsky: no interchange
Stop Rumyantsevo: no interchange
Stop Troparyovo: 950
Bus 272: Vnukovo Moskovsky Rumyantsevo Troparyovo
Bus 32: Tolstopaltsevo Marushkino Vnukovo
Bus 32K: Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo
Bus 950: Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo
```