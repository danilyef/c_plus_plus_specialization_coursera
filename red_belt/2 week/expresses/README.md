### Programming Assignment: Expresses

You are given a task and its solution - correct, but not meeting the specified time constraints. Rework this solution and submit it to the system.

### Condition
Develop a simple routing system for expresses traveling along a single railway direction represented as a straight line. Your program should be able to process two types of requests:

- `ADD start finish` - add an express route to the system, traveling from station start to station finish and back. The express does not make intermediate stops. Stations are represented by integers equal to their distance from the station (which is assigned the number 0).
- `GO start finish` - attempt to create a non-stop route from station start to station finish. If there is an express between these two stations, output 0 in response to this request. Otherwise, output a positive number - the minimum distance to which you can approach station finish, starting strictly from station start and using no more than one express.

### Input Format
The first line contains the number of queries Q - a natural number not exceeding 10^5. The following Q lines input queries according to the format described above. It is guaranteed that the station numbers are integers not exceeding 10^9 in absolute value.

### Output Format
For each GO query, output a single non-negative integer - the minimum distance to the final station of the route, calculated in accordance with the rules described above.

### Constraints
1 second to execute all queries. All guarantees described in the condition are valid for all tests on which your program will run. There is no need to check the correctness of the tests.

### Example

**Input:**

```
7
ADD -2 5
ADD 10 4
ADD 5 8
GO 4 10
GO 4 -2
GO 5 0
GO 5 100

Output
0
6
2
92
``` 

### Commentary on the example
In the first GO query, it is advantageous to use the express 10 4. In the second, it is better to stay in place than to use the express. In the third and fourth GO queries, it is necessary to use the expresses -2 5 and 5 8, respectively.
