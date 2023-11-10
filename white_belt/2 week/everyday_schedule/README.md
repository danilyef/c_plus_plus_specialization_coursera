#### Programming Task: Monthly To Do ####

Each of us has monthly tasks, each of which needs to be done on a specific day of each month: payment of electricity bills, subscription fees for communications, etc. You need to implement work with a list of such tasks, namely, the processing of the following operations:

**ADD *i s***

Add a case with the name ***s*** on the day ***i***.

**NEXT**

End the current month and start a new one. If the new month has more days than the current month, the added days will initially contain no cases. If there are fewer days in the new month, cases from all deleted days will need to be moved to the last day of the new month.

Please note that the number of commands of this type can exceed 11.

**DUMP *i***

Output all cases on the day ***i***.

Initially, the current month is January. The number of days in the months correspond to the Gregorian calendar, with the only difference being that February always has 28 days.

**NEXT**

Go to the to-do list for the new month. When this command is executed, instead of the current (old) to-do list for the current month, a (new) to-do list for the next month is created and becomes active: all tasks from the old to-do list are copied to the new list. After executing this command, the new to-do list and the next month become current, and work with the old to-do list is stopped. When moving to a new month, you need to pay attention to the different number of days in months:

* if the next month has more days than the current one, the "additional" days must be left empty (not containing cases);
* if the next month has fewer days than the current one, fewer days, cases from all "extra" days must be moved to the last day of the next month.

##### Notes #####

* The history of to-do lists is ***not required***, work is done only with the current to-do list of the current month. What's more, when creating a to-do list for the next month, it "***flashes***" the previous list.
* Please note that the number of ***NEXT*** commands in the total sequence of commands when working with the to-do list can exceed 11.
* The initial current month is January.
* The number of days in the months correspond to the Gregorian calendar, with the only difference being that February always has 28 days.

##### Input format #####
First, the number of operations *Q*, then the descriptions of the operations.

Case names ***s*** are unique and consist only of Latin letters, numbers and underscores. Day numbers ***i*** are integers and are numbered from 1 to the size of the current month.

##### Output format #####
For each operation of the **DUMP** type, on a separate line print the number of tasks on the corresponding day, and then their names, separating them with a space. The order in which cases are displayed within each operation does not matter.

##### Example #####
###### Input ######
```objectivec
12
ADD 5 Salary
ADD 31 Walk
ADD 30 WalkPreparations
NEXT
DUMP 5
DUMP 28
NEXT
DUMP 31
DUMP 30
DUMP 28
ADD 28 Payment
DUMP 28
```

###### Output ######
```objectivec
1 Salary
2 WalkPreparations Walk
0
0
2 WalkPreparations Walk
3 WalkPreparations Walk Payment
```

##### Notes #####
To append all elements of the *v2* vector to the end of the *v1* vector, it is convenient to use the *insert* method:

```objectivec
v1.insert(end(v1), begin(v2), end(v2));
```

In addition, a vector element can be of any type, including another vector. For example, vector<vector<int>> is a vector whose elements are vectors of integers (that is, a two-dimensional array). Usage example:

```objectivec
vector<vector<int>> m(10); // Create a vector of ten vectors of integers
m[0].push_back(5);  // Add elements to the first vector
m[0].push_back(15);
cout << m[0][1]; // Prints 15 - the second element of the first vector

m[1].push_back(3);
for (int x : m[1]) {
    // Loop through all the elements of the second 
}
```