### Programming Task: Queue 

People stand in line, but they never leave the beginning, but they can come to the end and leave from there. Moreover, sometimes some people may stop and start to worry about the fact that the queue is not moving forward.

Implement processing of the following operations on the queue:

- **WORRY *i***: mark the ***i***th person from the beginning of the queue (numbered from 0) as worried;
- **QUIET *i***: mark the ***i***th person as calm;
- **COME *k***: add ***k*** calm people to the end of the queue;
- **COME *-k***: remove ***k*** people from the end of the queue;
- **WORRY_COUNT**: Get the number of worried people in the queue.

The queue is initially empty.

### Input format 
Number of operations *Q*, then descriptions of operations.

For each **WORRY *i*** and **QUIET *i*** operation, it is guaranteed that a person with number ***i*** exists in the queue at the time of the operation.

For each **COME *-k*** operation, it is guaranteed that ***k*** is not greater than the current queue size.

### Output format 
For each **WORRY_COUNT** operation, print one integer — the number of worried people in the queue.

### Example 
**Input**
```objectivec
8
COME 5
WORRY 1
WORRY 4
COME -2
WORRY_COUNT
COME 3
WORRY 3
WORRY_COUNT
```

**Output**
```objectivec
1
2
```