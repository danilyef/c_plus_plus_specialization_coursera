### Programming Task: Common Fraction Calculator 

So, now you and I have a full-fledged type for representing ordinary fractions: the *Rational* class is integrated into the language using operator overloading and does not allow you to perform incorrect operations by throwing exceptions. Let's create a simple fraction calculator based on the *Rational* class.

You need to write a program that reads a single line from standard input in the format ***FRACTION_1 operation FRACTION_2***. *FRACTION_1* and *FRACTION_2* have the format *X/Y*, where *X* is an integer and *Y* is a non-negative integer. operation is one of the symbols *'+', '-', '*', '/'*.
If *FRACTION_1* or *FRACTION_2* is an invalid fraction, your program should print *"Invalid argument"* to standard output. If the read operation is division by zero, print the message *"Division by zero"* to standard output. Otherwise, print the result of the operation.

### Example 
|             stdin              |             stdout             |
|:------------------------------:|:------------------------------:|
| 1/2 + 1/3                      | 5/6                            |
| 1/2 + 5/0                      | Invalid argument               |
| 4/5 / 0/8                      | Division by zero               |