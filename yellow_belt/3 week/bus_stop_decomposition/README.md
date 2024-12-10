### Programming Task: Program Decomposition - 2 


In the [Program Decomposition] task, we split the monolithic code into a set of functions and classes. Now we will take one more step and split our program into several files. In this task, you need to create a project consisting of the following files:

- *query.h*, contains:
  - enum class QueryType
  - struct Query
  - declaration of istream& operator >> (istream& is, Query& q)
- *query.cpp*, contains:
  - definition of istream& operator >> (istream& is, Query& q);
- *responses.h*, contains:
  - struct BusesForStopResponse
  - ostream& operator << (ostream& os, const BusesForStopResponse& r)
  - struct StopsForBusResponse
  - ostream& operator << (ostream& os, const StopsForBusResponse& r)
  - struct AllBusesResponse
  - ostream& operator << (ostream& os, const AllBusesResponse& r)
- *responses.cpp*: definitions of everything declared in *responses.h*
- *bus_manager.h*: declaration of class *BusManager*
- *bus_manager.cpp*: definitions of *BusManager* class methods
- *main.cpp*: *main* function

task is "Bus and stops" from the White Belt.