### Programming Task: Synonyms 

Two words are called *synonyms* of each other if they have similar meanings. Implement the following operations on the synonym dictionary:

- **ADD *word1* *word2*** — add a pair of synonyms (***word1, word2***) to the dictionary.
- **COUNT *word*** — find out the number of synonyms for the word ***word***.
- **CHECK *word1* *word2*** — check if the words ***word1*** and ***word2*** are synonyms. The words ***word1*** and ***word2*** are considered synonyms if among the **ADD** queries there was at least one query **ADD *word1 word2*** or **ADD *word2 word1** *.

### Input format 
First enter the number of requests *Q*, then *Q* lines with descriptions of requests. It is guaranteed that in each query **CHECK** and **ADD** the words ***word1*** and ***word2*** are different. All words consist only of Latin letters, numbers and underscores.

### Output format 
For each request, print the answer to it in the corresponding line:

* In response to the query **COUNT *word*** print a single integer — the number of synonyms for the word ***word***.
* In response to the query **CHECK *word1 word2*** print the string **YES** if ***word1*** and ***word2*** are synonyms, and **NO** otherwise .

### Example 
**Input**
```objectivec
8
ADD program code
COUNT cipher
ADD code cipher
COUNT code
COUNT program
CHECK code program
CHECK program cipher
CHECK cpp java
```

**Output**
```objectivec
0
2
1
YES
NO
NO
```