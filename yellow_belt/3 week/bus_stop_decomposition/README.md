#### Programming Task: Program Decomposition - 2 ####


In the [Program Decomposition] task, we split the monolithic code into a set of functions and classes. Now we will take one more step and split our program into several files. In this task, you need to create a project consisting of the following files:

1. *query.h*, в него кладём:
* enum class QueryType
* struct Query
* объявление istream& operator >> (istream& is, Query& q)
2. *query.cpp*, в него кладём
* определение istream& operator >> (istream& is, Query& q);
3. *responses.h*:
* struct BusesForStopResponse
* ostream& operator << (ostream& os, const BusesForStopResponse& r)
* struct StopsForBusResponse
* ostream& operator << (ostream& os, const StopsForBusResponse& r)
* struct AllBusesResponse
* ostream& operator << (ostream& os, const AllBusesResponse& r)
4. *responses.cpp*: определения всего, что объявлено в *responses.h*
5. *bus_manager.h*: объявление класса *BusManager*
6. *bus_manager.cpp*: определения методов класса *BusManager*
7. *main.cpp*: функция *main*

task is "Bus and stops" from the White Belt.