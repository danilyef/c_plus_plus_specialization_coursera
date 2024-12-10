### Final Project: Database 

### Introduction
In the course "C++ White Belt," the final task was to develop a database that works with pairs (date, event). In this task, you need to expand this database by teaching it to select and delete events that satisfy a given condition. Additionally, you should organize the code into multiple files.

In more detail, your program should be able to process the following commands:

- `Add date event`: Add the pair (date, event) to the database.
- `Print`: Output the entire contents of the database.
- `Find condition`: Output all records in the database that satisfy the condition.
- `Del condition`: Delete from the database all records that satisfy the condition.
- `Last date`: Output the record with the latest event that occurred not later than the given date.

The conditions in the Find and Del commands impose certain restrictions on dates and events, for example:

- `Find date < 2017-11-06`: Find all events that occurred before November 6, 2017.
- `Del event != "holiday"`: Delete from the database all events except "holiday."
- `Find date >= 2017-01-01 AND date < 2017-07-01 AND event == "sport event"`: Find all "sport event" events that occurred in the first half of 2017.
- `Del date < 2017-01-01 AND (event == "holiday" OR event == "sport event")`: Delete from the database all "holiday" and "sport event" events that occurred before 2017.

Conditions in both types of commands can be empty, and in such cases, all events are considered.

### Program Structure

Below are templates for files:

- `condition_parser.h/cpp`: In the lecture "Parsing Arithmetic Expressions. Description of the Solution," we demonstrated the construction of an abstract syntax tree for arithmetic expressions. The implementation of this algorithm for parsing conditions in Find and Del commands is contained in the `ParseCondition` function, declared and fully implemented in the `condition_parser.h/cpp` files.
- `token.h/cpp`: Contains a ready-made tokenizer used in the `ParseCondition` function.
- `main.cpp`: Contains the main function.

You need to analyze the provided code and develop the missing classes and functions:

- `Database` class, representing the database. You should create its public interface based on how it is used in the `main` function.
- `Node`, `EmptyNode`, `DateComparisonNode`, `EventComparisonNode`, and `LogicalOperationNode` classes. Formulate their hierarchy and public interface by analyzing the `main` function and `ParseCondition` function.
- `Date` class, as well as the `ParseDate` function and output stream operator for the `Date` class.

For the review, you should send an archive consisting of files:

- `date.h/cpp`: These files should contain declarations and definitions for the `Date` class, the `ParseDate` function, and the output stream operator for the `Date` class.
- `database.h/cpp`: These files should contain the declaration and definition of the `Database` class.
- `node.h/cpp`: These files should contain declarations and definitions for the `Node` class and all its descendants (see above), representing nodes of the abstract syntax tree formed by the `ParseCondition` function.
- `condition_parser.h/cpp`.
- `token.h/cpp`.
- `main.cpp`.
- Any other `.h` and `.cpp` files that you deem necessary to create in your solution.





### How your solution will be tested

Testing your solution will be carried out in two stages. In the first stage, the automatic testing system will unpack the archive you send and compile the extracted files into an executable. Then, this executable will be run on a set of tests. The testing process is similar to most tasks in our course—input is fed into stdin, the program's execution time is measured, and the stdout is analyzed.

In the second stage, individual files of your project will be tested. It will be verified that the `date.h` file indeed contains the declaration of the `Date` class, that `Database::FindIf` correctly performs the search according to the passed predicate, etc. We expect your classes to have an interface fixed in the `main` function. Therefore, in the `Database` and `Node` classes, make the methods have the same signatures as those used in the `main` function.

### Input and Output Format

Commands for working with the database are provided in standard input, one command per line. Your program should read them and output the processing results to standard output. The rules for processing commands are outlined below.

### Command: Add

Upon encountering the command `Add date event`, your program should add the pair `(date, event)` to the database and then display it when searching (command `Find`) or printing (command `Print`). Identical events occurring on the same day need not be preserved: adding an already existing pair `(date, event)` to the database should be ignored. On the same date, many different events can occur, and the database should be able to save them all.

It is guaranteed that the `date` field in the `Add` command has the format "Year-Month-Day," where Year is an integer from 0 to 9999, Month is the month number from 1 to 12, and Day is the day number from 1 to 31. After the date, there must be a space separating it from the event. Examples of valid dates: 2017-11-07, 0-2-31.

The rest of the string in the `Add` command specifies the event. It may contain spaces, so `getline` can be used to read it. However, it is guaranteed that the event name cannot contain a quotation mark ("). Thus, this symbol can only occur in the condition in the `Find` and `Del` commands, serving as a delimiter for the event name.

**Example**

For the command `Add 2017-11-07 big sport event`, the program should add the pair `(2017-11-07, big sport event)` to the database.

### Command: Del

Upon encountering the command `Del condition`, your program should remove from the database all events that satisfy the condition, and output the number of removed entries `N` in the format "Removed N entries" to standard output. If the condition is empty, the execution result of the command should be the clearing of the entire database.

**Example**

**Input:**

```
Add 2017-06-01 1st of June
Add 2017-07-08 8th of July
Add 2017-07-08 Someone's birthday
Del date == 2017-07-08
```

**Output:**

```
Removed 2 entries
```

### Command: Print

Upon encountering the command `Print`, your program should output all pairs `(date, event)` currently in the database to standard output. Pairs should be output one per line, sorted by date in ascending order. Events within the same date should be output in the order they were added (except for already deleted and attempts to add duplicates).

Dates should be output in the format YYYY-MM-DD, where Y, M, D are the digits of the year, month, and day, respectively. If any number has fewer digits than required, it should be padded with zeros, for example, 0001-01-01 is the first of January of the first year.

**Example**

**Input:**

```
Add 2017-01-01 Holiday
Add 2017-03-08 Holiday
Add 2017-1-1 New Year
Add 2017-1-1 New Year
Print
```

**Output:**

```
2017-01-01 Holiday
2017-01-01 New Year
2017-03-08 Holiday
```

Note that the event "New Year" is only output once, despite being added twice. As mentioned in the description of the `Add` command, identical events occurring on the same day need not be preserved.

### Command: Find

Upon encountering the command `Find condition`, your program should output all pairs `(date, event)` currently in the database that satisfy the condition. The output format is similar to the `Print` command. A search with an empty condition is equivalent to the `Print` command. At the end, the command should output the line "Found N entries," where N is the number of found pairs.

**Example**

**Input:**

```
Add 2017-01-01 Holiday
Add 2017-03-08 Holiday
Add 2017-01-01 New Year
Find event != "working day"
Add 2017-05-09 Holiday
```

**Output:**

```
2017-01-01 Holiday
2017-01-01 New Year
2017-03-08 Holiday
Found 3 entries
```

### Command: Last

For the command `Last date`, output the last event that occurred on or before the given date. More formally:

- Find the largest date among all existing events that does not exceed the given date.
- Among all events with that date, select the last one added and output it in the format similar to the `Print` command.
- If the date is earlier than all existing dates, output "No entries."

**Example**

**Input:**

```
Add 2017-01-01 New Year
Add 2017-03-08 Holiday
Add 2017-01-01 Holiday
Last 2016-12-31
Last 2017-01-01
Last 2017-06-01
Add 2017-05-09 Holiday
```

**Output:**

```
No entries
2017-01-01 Holiday
2017-03-08 Holiday
```

**Example**

**Input:**

```
Add 2017-11-21 Tuesday
Add 2017-11-20 Monday
Add 2017-11-21 Weekly meeting
Print
Find event != "Weekly meeting"
Last 2017-11-30
Del date > 2017-11-20
Last 2017-11-30
Last 2017-11-01
```

**Output:**

```
2017-11-20 Monday
2017-11-21 Tuesday
2017-11-21 Weekly meeting
2017-11-20 Monday
2017-11-21 Tuesday
Found 2 entries
2017-11-21 Weekly meeting
Removed 2 entries
2017-11-20 Monday
No entries
```



