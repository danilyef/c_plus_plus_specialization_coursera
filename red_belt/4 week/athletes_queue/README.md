#### Programming Task "Athletes"

Condition
Each athlete has a unique number written on their jersey. Athletes come out of the locker room one by one and must line up on the field. The coach tells each exiting athlete the number of the athlete they should stand behind. If there is no athlete with the specified number on the field, the athlete should stand at the end of the line.

In the standard input, first, a natural number n is given, not exceeding 100000, which is the number of athletes. Then follow n pairs of non-negative integers, not exceeding 100000. The first number in the pair is the number of the current exiting athlete. The second number in the pair is the number of the athlete behind whom the current one should stand.

Print to standard output the numbers of the athletes in the order of their arrangement on the field.

Time limit: 0.8 s.

Example
Input

5
42 0 
17 42 
13 0 
123 42
5 13

Output

17 123 42 5 13