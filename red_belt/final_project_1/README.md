#### Programming Task: Search Engine

It would be strange to have a course from Yandex and not ask you to create your own search engine. In the final task of the "Red Belt" course, this is exactly what we will be doing :)

In this task, you need to work with the `SearchServer` class, which allows you to search a database of documents:

```cpp
class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);

  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);
};
```

Let's consider its interface.

#### Constructor
The constructor of the `SearchServer` class takes an input stream containing the document database. Here,

- One document is one line of the input stream;
- Documents consist of words separated by one or more spaces;
- Words consist of lowercase Latin letters.

For example, the code below loads a database of three documents into an object of the `SearchServer` class:

```cpp
string docs;
docs += "london is the capital of great britain\n";  // document contains 7 words
docs += "i am travelling down the river\n";          // document contains 6 words
docs += "  here     we    go             ";          // document contains 3 words

istringstream document_input(docs);
SearchServer srv(document_input);
```

#### Method `AddQueriesStream(istream& query_input, ostream& search_results_output)`
The `AddQueriesStream` method performs the actual search. It takes an input stream of search queries and an output stream for writing the search results. Here,

- One query is one line in the `query_input` stream;
- Each search query consists of words separated by one or more spaces;
- Just like in the documents, words in the queries consist of lowercase Latin letters.

The result of processing a search query is a set of up to five most relevant documents. In real search engines, the relevance metric is quite complex. In our task, we will use the total number of occurrences of all query words in the document as the relevance metric. For example, suppose we have a search database of three documents: "london is the capital of great britain", "moscow is the capital of the russian federation", "paris is the capital of france", and a search query "the best capital". The relevance metric for our documents will be:

- "london is the capital of great britain" — 2 (the word "the" appears once, the word "best" — not at all, the word "capital" — once)
- "moscow is the capital of the russian federation" — 3 (the word "the" appears twice, the word "best" — not at all, the word "capital" — once)
- "paris is the capital of france" — 2 ("the" — 1, "best" — 0, "capital" — 1)

As a result, the document "moscow is the capital of the russian federation" turns out to be the most relevant to the query "the best capital".

For each search query, the `AddQueriesStream` method should output one line in the `search_results_output` stream in the format `[query text]: {docid: <value>, hitcount: <value>} {docid: <value>, hitcount: <value>} ...`, where `docid` is the document identifier (see below), and `hitcount` is the relevance metric value for that document (i.e., the total number of occurrences of all query words in that document).

Two important notes:

- Do not include documents with a `hitcount` of zero in the search results.
- When counting the `hitcount`, only whole words should be considered, i.e., the word "there" is not a match for the word "the".

#### Method `UpdateDocumentBase(istream& document_input)`
The `UpdateDocumentBase` method replaces the current document database with a new one contained in the `document_input` stream. The document from the first line of this stream will have the identifier (docid) 0, the document from the second line — identifier 1, and so on. The constructor of the `SearchServer` class should assign identifiers to documents in the same way. For example, the code

```cpp
const string doc1 = "london is the capital of great britain";
const string doc2 = "moscow is the capital of the russian federation";
istringstream doc_input1(doc1 + '\n' + doc2);
SearchServer srv(doc_input1);

const string query = "the capital";
istringstream query_input1(query);
srv.AddQueriesStream(query_input1, cout);

istringstream doc_input2(doc2 + '\n' + doc1);
srv.UpdateDocumentBase(doc_input2);
istringstream query_input2(query);
srv.AddQueriesStream(query_input2, cout);
```

should output

```
the capital: {docid: 1, hitcount: 3} {docid: 0, hitcount: 2}
the capital: {docid: 0, hitcount: 3} {docid: 1, hitcount: 2}
```

#### Part One of the Task
This task consists of two parts. In the first part, you are given a correct implementation of the `SearchServer` class that works too slowly. You need to find and eliminate bottlenecks in its implementation. You should submit a `.cpp` file or an archive of several source files containing your optimized implementation. Your implementation will be tested with the following function (an object of the `SearchServer` class will be created once, and its `AddQueriesStream` method will be called once):

```cpp
void TestSearchServer(istream& document_input, istream& query_input,
                      ostream& search_results_output) {
  SearchServer srv(document_input);
  srv.AddQueriesStream(query_input, search_results_output);
}
```

Here,

- `document_input` contains no more than 50,000 documents;
- Each document contains no more than 1,000 words;
- The total number of different words in all documents does not exceed 10,000;
- The maximum length of one word is 100 characters, words consist of lowercase Latin letters and are separated by one or more spaces;
- `query_input` contains no more than 500,000 queries, each query contains from 1 to 10 words.

Refer to the unit tests in the solution template for more details on how the `SearchServer` class should work.