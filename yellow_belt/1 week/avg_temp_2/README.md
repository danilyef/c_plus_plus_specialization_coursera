### Programming Task: Average Temperature - 2 

Temperature values ​​observed during N successive days are given. Find the numbers of days (numbered from zero) with a temperature value above the arithmetic mean for all N days.

It is guaranteed that the arithmetic mean of the temperature values ​​is an integer.

### Input format 

The number N is entered, then N integers — the temperature values ​​on the 0th, 1st, ... (N−1)th day. It is guaranteed that N does not exceed a million (10^6), and the temperature values, measured in millionths of degrees Celsius, range from −10^8 to 10^8. You don't need to check for these restrictions: you can use them as a guide when choosing the most appropriate types for your variables.

### Output format 

The first number K is the number of days in which the temperature value is above the arithmetic mean. Then K integers are the numbers of these days.

### Example 

**Input**
```commandline
5
5 4 1 -2 7
```

**Output**
```commandline
3
0 1 4
```