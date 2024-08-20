
#### Programming Task: Demographic Indicators 2.0

You’ve started a new job and joined a long-standing project. The project involves researching various indicators based on census results. As is often the case, the project started as a simple system solving one problem, but over time, new features were added to it, usually in a rush and at the last minute.

The initial task of the project was to model the change in the age of adulthood. Experimenters would input different ages of adulthood and study how many people in the society would be adults under those conditions. This information was used to calculate annual budgets, personal income tax collection plans, and so on.

The first version of the program accepted a list of all people living in the state, obtained through the census. It then processed a stream of commands of the form "AGE N". For each such command, the program would output "There are X adult people for maturity age N", where X is the number of people whose age is at least N. The program worked excellently and handled lists of several million people.

But then the management urgently wanted more features. A new command, "WEALTHY M", was introduced, for which the program had to output the total income of the top M wealthiest people in the format "Top-M people have total income X".

Before the testing of the new functionality was completed, management demanded immediate support for the command "POPULAR_NAME M/W", where the program was required to report the most popular male or female name as "Most popular name among people of gender M is Ivan".

The previous team quickly implemented this functionality 2 hours before the deadline, ensured it worked correctly on simple tests, and delivered the program to the client. Naturally, the program did not work for the client, and they asked for it to be fixed, sending a detailed description of the errors found. It looked like this: “Your program doesn’t work at all! Fix it urgently, or I will sue.”

Naturally, the previous team was immediately fired and you were hired =) So, you have the program and the only test on which it was tested. You need to make it work properly.

**Input Format**
The program receives a number N — the number of people. Following this are N lines in the format: Name Age Income Gender. After that, commands follow, one per line.

Types of commands:

- **AGE N** — The program should output "There are X adult people for maturity age N", where X is the number of people whose age is at least N.

- **WEALTHY M** — The program should output "Top-M people have total income X", where X is the total income of the top M wealthiest people.

- **POPULAR_NAME M** — The program should output "Most popular name among people of gender M is S", where S is the most common male name. If there are multiple such names, output the lexicographically smallest one. If there are no such names, output "No people of gender M".

- **POPULAR_NAME W** — The program should output "Most popular name among people of gender W is S", where S is the most common female name. If there are multiple such names, output the lexicographically smallest one. If there are no such names, output "No people of gender W".

**Example**
**Input**

```
11
Ivan 25 1000 M
Olga 30 623 W
Sergey 24 825 M
Maria 42 1254 W
Mikhail 15 215 M
Oleg 18 230 M
Denis 53 8965 M
Maxim 37 9050 M
Ivan 47 19050 M
Ivan 17 50 M
Olga 23 550 W
AGE 18
AGE 25
WEALTHY 5
POPULAR_NAME M
```

**Output**

```
There are 9 adult people for maturity age 18
There are 6 adult people for maturity age 25
Top-5 people have total income 39319
Most popular name among people of gender M is Ivan
```