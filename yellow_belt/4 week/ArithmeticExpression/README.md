#### Construction of an arithmetic expression: Part 1####

Implement the construction of an arithmetic expression according to the following scheme:

Initially, there is an expression consisting of some integer x.
At each step, a certain operation is applied to the current expression: 
- addition of a number
- subtraction of a number
- multiplication by a number or division by a number; 

before applying the operation, the expression must always be enclosed in parentheses.

Input Format:
The first line contains the initial integer x. The second line contains a non-negative integer N, which represents the number of operations. Each of the following N lines contains one operation:

- Addition of a number a: + a;
- Subtraction of a number b: - b;
- Multiplication by a number c: * c;
- Division by a number d: / d.

The number of operations can be zero. In this case, you should output the initial number.

Output Format:
Output a single line containing the constructed arithmetic expression.

Pay attention to the spacing around the symbols:

- Each binary operation symbol (+, -, *, or /) should be surrounded by exactly one space on each side: (8) * 3;
- The symbol for unary minus (for negative numbers) does not require additional spaces: -5;
- Parentheses and numbers do not need extra spaces.

Example: 

- Input: 
```objectivec
8
3
* 3
- 6
/ 1
```

- Output:
```objectivec
(((8) * 3) - 6) / 1
```
