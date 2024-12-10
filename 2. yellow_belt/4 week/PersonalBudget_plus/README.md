### Personal Budget: Plus edition 

"Personal Budget," starter version
Implement a personal budget management system. You need to process requests of the following types:

ComputeIncome from to: calculate the net income for the given date range.

Earn from to value: consider that the amount value was earned evenly over the specified period (per day).

### Notes:

Both dates 'from' and 'to' are inclusive in all date ranges.

### Input Format
The first line contains the number of queries Q, followed by the queries themselves in the format described above, one per line.

### Output Format
For each ComputeIncome query, output a floating-point number in a separate line, representing the profit for the specified date range.

### Note:

Use std::cout.precision(25) in your code for consistent formatting of floating-point numbers.

### Constraints
The number of queries Q is a natural number not exceeding 50.

All dates are in the format YYYY-MM-DD. Dates are valid (accounting for leap years) and belong to the interval from 2000 to 2099.

Value is a positive integer not exceeding 1000000.

1 second for processing all queries.

