#### Programming task: Selection of palindromes ####

Write a function that

* is called *PalindromFilter*
* returns *vector<string>*
* takes *vector<string>* words and *int minLength* and returns all strings from vector words that are palindromes and have length at least *minLength*

The input vector contains no more than 100 lines, the length of each line is no more than 100 characters.

##### Examples #####

|              words             |            minLength           |            результат           |
|:------------------------------:|:------------------------------:|:------------------------------:|
| abacaba, aba                   | 5                              |  abacaba                       |
| abacaba, aba                   | 2                              |  abacaba, aba                  |
| weew, bro, code                | 4                              |  weew                          |