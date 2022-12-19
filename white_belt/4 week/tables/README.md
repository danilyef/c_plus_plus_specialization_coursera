#### Programming Task: Reading and Displaying a Table ####

The first line of the file *input.txt* contains two numbers *N* and *M*. Further in the file is a table with *N* rows and *M* columns, presented in *CSV (comma-separated values)* format. This format is often used for text representation of tables with data: there are several lines in the file, values ​​from different cells inside the line are separated from each other by commas. Your task is to display the data on the screen in the form of a table, the cell size of which is 10, adjacent cells are separated from each other by a space. There should not be a space after the last cell. It is guaranteed that the table will have exactly *N* rows and *M* columns, the value of each of the cells is an integer.

##### Input #####
```objectivec
2 3
1,2,3
4,5,6
```

##### Output #####
```objectivec
         1          2          3
         4          5          6
```