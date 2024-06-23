#### Programming Task: Search Engine

#### Part Two of the Task
In this part, we will simulate the operation of a web server that simultaneously handles multiple streams of search queries as well as document base updates. Your implementation will be tested as follows:

```cpp
void TestSearchServer(vector<pair<istream, ostream*>> streams) {
  // IteratorRange — a template from the Paginator task
  // random_time() — a function that returns a random time interval

  LOG_DURATION("Total");
  SearchServer srv(streams.front().first);
  for (auto& [input, output] :
       IteratorRange(begin(streams) + 1, end(streams))) {
    this_thread::sleep_for(random_time());
    if (!output) {
      srv.UpdateDocumentBase(input);
    } else {
      srv.AddQueriesStream(input, *output);
    }
  }
}
```

As you can see, we measure the total runtime of the testing function using the `LOG_DURATION` macro. Your implementation should work faster than simply applying the `UpdateDocumentBase` and `AddQueriesStream` methods sequentially.

In practice, such a web server spends most of its time processing search queries. The document database is updated infrequently and periodically, for example, once a day. Updating the database can take a significant amount of time, so the server should not stop processing queries while this is happening. Your solution for the second part of the task should take this into account.

The `AddQueriesStream` method should be prepared to run concurrently with the `UpdateDocumentBase` method and vice versa.

The `AddQueriesStream` method does not have to process all queries with the version of the document database that was current when it started. That is, if the document database was updated during the execution of the `AddQueriesStream` method, it can use the new version of the database for processing the remaining queries.