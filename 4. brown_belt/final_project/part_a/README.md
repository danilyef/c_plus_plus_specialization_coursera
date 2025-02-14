### Programming Task  
**"Transport Directory, Part A"**  

In this task and its subsequent versions, you need to implement a system for storing transport routes and processing queries. First, database creation requests are provided as input, followed by queries to the database itself.  

When designing your solution, keep in mind that it will need to be expanded multiple times. You will only see the official solutions after successfully completing all versions. This means that throughout the development process, you will work with your own code architecture and experience firsthand which design decisions hinder expansion.  

**Do not neglect unit tests!** They will ensure that changes to one part of the functionality do not break the rest of the system.  

As in other tasks, you can submit an archive containing multiple files for verification.  

---

### Database Input Format  
The first line contains the number of database update requests, followed by the requests themselves, one per line. There are two types of requests:  

- **Stop X: latitude, longitude**  
  Defines a stop named **X** with coordinates **latitude** and **longitude**.  
  - A stop is guaranteed to be defined in at most one **Stop X** request.  

- **Bus X: route description**  
  Defines a bus route **X**. The route description can be in one of two formats:  

  - `stop1 - stop2 - ... - stopN`  
    - The bus travels from **stop1** to **stopN** and back, stopping at the intermediate stops.  

  - `stop1 > stop2 > ... > stopN > stop1`  
    - A circular route ending at **stop1**.  

  Essentially, the first format is equivalent to:  
  `stop1 > stop2 > ... > stopN-1 > stopN > stopN-1 > ... > stop2 > stop1`  

  - Every stop in the route is guaranteed to be defined in a **Stop** request.  
  - Each route **X** is defined at most once.  

---

### Query Format  
The first line contains the number of database queries, followed by the queries themselves, one per line. For now, there is only one type of query:  

- **Bus X**  
  - Prints information about bus **X** in the following format:  
    ```
    Bus X: R stops on route, U unique stops, L route length
    ```
    - **R** — number of stops in the route, including both directions or the full loop.  
    - **U** — number of unique stops where the bus stops (stops with the same name are considered identical).  
    - **L** — route length in meters, assuming the bus travels the shortest distance between two consecutive stops on Earth's surface.  

    - Use **π = 3.1415926535** and **Earth's radius = 6371 km** when computing distances.  
    - Display floating-point values with **6 significant digits** using `setprecision(6)`.  
    - Values are compared with a relative error tolerance of **0.0001**, not character-by-character.  

  - If the bus **X** is not found, print:  
    ```
    Bus X: not found
    ```


- **Stop X**  
Prints information about stop **X** in the following format:  
```
Stop X: buses bus1 bus2 ... busN
```
- **bus1 bus2 ... busN** — List of buses that pass through stop **X**.  
  - Duplicates are **not allowed**.  
  - Bus names must be **sorted alphabetically**.  

If stop **X** is **not found**, print:  
```
Stop X: not found
```  
If stop **X** exists in the database but **no buses pass through it**, print:  
```
Stop X: no buses
```  

---

### Constraints  
- **1 second** to process all queries.  
- **≤ 2000** database update requests.  
- **≤ 2000** database queries.  
- **≤ 100** stops per route.  
- **≤ 25 characters** for bus and stop names (Latin letters, digits, and spaces only).  
- Names are **non-empty**, cannot start or end with spaces.  

---

### **Example**  

#### **Input**
```
13
Stop Tolstopaltsevo: 55.611087, 37.20829
Stop Marushkino: 55.595884, 37.209755
Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye
Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka
Stop Rasskazovka: 55.632761, 37.333324
Stop Biryulyovo Zapadnoye: 55.574371, 37.6517
Stop Biryusinka: 55.581065, 37.64839
Stop Universam: 55.587655, 37.645687
Stop Biryulyovo Tovarnaya: 55.592028, 37.653656
Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164
Bus 828: Biryulyovo Zapadnoye > Universam > Rossoshanskaya ulitsa > Biryulyovo Zapadnoye
Stop Rossoshanskaya ulitsa: 55.595579, 37.605757
Stop Prazhskaya: 55.611678, 37.603831
6
Bus 256
Bus 750
Bus 751
Stop Samara
Stop Prazhskaya
Stop Biryulyovo Zapadnoye
```

#### **Output**
```
Bus 256: 6 stops on route, 5 unique stops, 4371.02 route length
Bus 750: 5 stops on route, 3 unique stops, 20939.5 route length
Bus 751: not found
Stop Samara: not found
Stop Prazhskaya: no buses
Stop Biryulyovo Zapadnoye: buses 256 828
```