#### Programming Task: Student List ####

Define a "Student" structure with the fields first name, last name, date, month, and year of birth. Create a vector of such structures, fill it from the input data, and then display the required fields when prompted.

##### Input format #####
The first line contains one integer *N* from 0 to 10000 - the number of students.

Next come *N* lines, each of which contains two lines from 1 to 15 characters long - the name and surname of the next student, and three integers from 0 to 1000000000 - the day, month and year of birth.

The next line contains a single integer *M* from 0 to 10000 - the number of requests.

The next *M* lines contain a string of 1 to 15 characters - the request, and an integer from 0 to 1000000000 - the student's number (numbering starts from 1).

##### Output format #####
For a query like **"name K"**, where *K* is from 1 to *N*, print the name and surname of the *K*-th student separated by a space.

For a query like **"date K"**, where *K* is from 1 to *N*, print the date, month, and year of birth of *K*-th student separated by a dot.

For other requests print **"bad request"**.

##### Example Code #####
```objectivec
3
Ivan Ivanov 1 1 1901
Petr Petrox 2 2 1902
Alexander Sidorov 3 3 1903
3
name 1
date 3
mark 5
```
##### Output #####
```objectivec
Ivan Ivanov
3.3.1903
bad request
```