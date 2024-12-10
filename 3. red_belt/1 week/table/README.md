### Programming Assignment: Table

You need to write a template class called Table for an electronic table. For simplicity, let's assume that all cells in the table have the same data type T. The table should be able to change its size as per the user's request. Newly created cells should be filled with default values of type T.

Here are the requirements for the class:

- The class should be named Table.
- The class should have a template parameter T - the type of the element in a cell.
- The class should have a constructor that takes two size_t parameters - the number of rows and columns, respectively.
- The class should have constant and non-constant versions of the [] operator, returning something to which the [] operator can be applied again. In other words, constructions like cout << table[i][j]; and table[i][j] = value; should work. It is not necessary to check the correctness of the indices.
- The class should have a function Resize, taking two size_t parameters and changing the size of the table. The old data that fits into the new size should be preserved.
- The class should have a constant method Size, returning a pair<size_t, size_t> representing the size of the table (in the same order as these arguments were passed to the constructor).