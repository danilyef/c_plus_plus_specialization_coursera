### Programming Task: Course Final Objective 

It is necessary to write a C ++ program that implements work with a simple database (abbreviated as "DB"). The program will communicate with the user via standard input and output (streams *stdin* and *stdout*).

We will store pairs of the form in our database: date, event. Let's define a date as a string of the form *Year-Month-Day*, where *Year*, *Month* and *Day* are integers.

Let's define an event as a string of arbitrary printable characters without separators inside (spaces, tabs, etc.). The event cannot be an empty string. Many different events can happen on the same date, the database must be able to save them all. You do not need to save identical events that occurred on the same day: it is enough to save only one of them.

Our database must understand certain commands in order to be able to interact with it:

```objectivec
- adding an event: Add Date Event
- delete event: Del Date Event
- deleting all events for a specific date: Del Date
- search for events for a specific date: Find Date
- printing of all events for all dates: Print
```

All commands, dates and events are separated by spaces when entered. Commands are read from standard input. There can be exactly one command per line, but you can enter multiple commands on multiple lines. Blank lines can also be received as input - they should be ignored and processing of new commands should be continued in subsequent lines.

### Adding an event (Add *Date* *Event*) 
When adding an event, the database should remember it and then show it when searching (with the Find command) or printing (with the Print command). If the specified event already exists for the given date, its re-adding should be ignored. In case of correct input (see section "Handling input errors") the program should not display anything on the screen.

### Delete event (Del *Date* *Event*) 
The command should remove the previously added event with the specified name on the specified date, if it exists. If the event is found and deleted, the program should output the string "Deleted successfully" (without quotes). If no event was found on the specified date, the program should output the string "Event not found" (without quotes).

### Deleting multiple events (Del *Date*) 
The command deletes all previously added events for the specified date. The program should always output a line like "Deleted N events", where N is the number of all found and deleted events. N can be zero if there were no events on the specified date.

### Event search (Find *Date*) 
Find and print previously added events on a specified date. The program should only print the events themselves, one per line. Events must be sorted in ascending order in order of comparing strings with each other (string type).

### Print all events (Print) 
With this command, we can show the full contents of our database. The program should print all Date Event pairs one per line. All pairs must be sorted by date, and events within the same date must be sorted in ascending order in order of comparing strings with each other (string type). Dates must be formatted in a special way: *YYYY-MM-DD*, where *Y*, *M*, *D* are the digits of the year, month, and day, respectively. If some number has fewer digits, then it must be padded with zeros, for example, 0001-01-01 is the first of January of the first year. You don't need to output a date with a negative year value.

### Handling input errors 
If the user entered an unknown command, then the program should report this by displaying the line *"Unknown command: COMMAND"*, where *COMMAND* is the command that the user entered. The command is the first word in the line (before a space).

If the date does not follow the format *Year-Month-Day*, where *Year*, *Month* and *Day* are arbitrary integers, then the program should print "Wrong date format: *DATE*", where *DATE* is what the user entered instead of the date (up to a space). Please note that the parts of the date are separated by exactly one hyphen, and the date itself must not contain extra characters either before the year or after the day. The date parts cannot be empty, but they can be zero or even negative.

If the date format is correct, the validity of the month and day must be checked.

• If the month number is not a number between 1 and 12, print "Month value is invalid: *MONTH*", where *MONTH* is an invalid month number, such as 13 or -1
• If the month is valid and the day is not between 1 and 31, print "Day value is invalid: *DAY*", where *DAY* is an invalid number of the day in the month, such as 39 or 0.

Note that:

• The year value does not need to be checked separately.
• No need to check the calendar correctness of the date: the number of days in each month is considered equal to 31, leap years do not need to be taken into account.
• If both month and day are incorrect, then one error message per month should be displayed.

After any error in entering and printing a message, the program must terminate its execution.

### Examples:

• 1-1-1 is a valid date;
• -1-1-1 — valid date (year -1, month 1, day 1);
• 1--1-1 — date in correct format, but with incorrect month -1;
• 1---1-1 - the date is in the wrong format: the month cannot start with two hyphens.

After processing any of the described errors in entering and printing a message, the program should terminate its execution.

Which input errors ***shouldn't*** be handled

We do not aim to break your program in every possible way, therefore, except as described in the previous paragraph, you can rely on the correctness of the input. In particular, we guarantee that:

• Each command occupies exactly one line in its entirety, although there may be empty lines in the input (they should be ignored).
• Events always contain the specified number of arguments: the Add command is always followed by the date and event, the Find command is always followed by the date, the Del command is always followed by the date and possibly the event, and the Print command does not contain additional information.
• All commands, dates and events are non-empty strings and do not contain spaces or other whitespace characters. (In particular, our tests do not contain the "Add 2018-02-12" command because it does not include the event name after the date.) On the other hand, the Del command may not contain events after the date: specified date (see section "Deleting multiple events").
• Even though a date with a negative year value is considered valid, the tests are designed so that it does not need to be printed in the Print command.

**Example**

**Correct Input:** 

```objectivec
Add 0-1-2 event1
Add 1-2-3 event2
Find 0-1-2

Del 0-1-2
Print
Del 1-2-3 event2
Del 1-2-3 event2
```
**Output:**

```objectivec
event1
Deleted 1 events
0001-02-03 event2
Deleted successfully
Event not found
```
**Incorrect date input:**

```objectivec
Add 0-13-32 event1
```
**Output:**

```objectivec
Month value is invalid: 13
```

**Uncaught exceptions**
Since the solution of the problem requires a program that works correctly on a large number of different input data, then errors can inevitably be found in it, some of which we did not talk about in our lecture course. One of these errors can be an uncaught exception: the error is that the exception, when thrown, does not fall under any of the catch block expressions up to the main function. In this case, the program will immediately crash, and you will see *"Unknown signal 6"* as an error in the test.
