### Programming Task: Pipeline

**Introduction**
Many programs are designed to batch-process large numbers of homogeneous records. Often, the processing of these records can be divided into logically independent stages, simplifying the joint development of new features and allowing these stages to be easily combined into new configurations. You can imagine such processing as a flow of objects moving along a pipeline from one handler to another. In this task, you are to complete the implementation of such a pipeline.

The main idea of the pipeline is to use functions that "consume" objects and call each other:

```cpp
void ConsumeObject(unique_ptr<SomeObject> obj) {
    // processing
    ConsumeObject2(move(obj));  // transfer ownership of the object
}
```

An architecture with `shared_ptr` is possible, but typically `unique_ptr` is sufficient and has advantages:

- Reduces overhead
- Clearly transfers ownership: it is assumed that once an object is passed on, the handler will no longer modify it, simplifying reasoning about the program's correctness.

Using classes instead of functions allows handlers to be decoupled from each other and simplifies support for multiple classes of processed objects.

**Problem Statement**
In this task, you are to develop a pipeline of email handlers:

```cpp
struct Email {
  string from;
  string to;
  string body;
};
```

Handlers should implement the abstract class `Worker`:

```cpp
class Worker {
public:
  virtual void Process(unique_ptr<Email> email) = 0;
  virtual void Run() {
    // only the first worker in the pipeline needs to implement this method
    throw logic_error("Unimplemented");
  }

protected:
  // implementations must call PassOn to pass the object further
  // down the chain of handlers
  void PassOn(unique_ptr<Email> email) const;

public:
  void SetNext(unique_ptr<Worker> worker);
};
```

You should also implement the handlers `Reader`, `Filter`, `Copier`, and `Sender`, which inherit from the `Worker` class, as well as the class `PipelineBuilder`, which constructs the chain of handlers:

```cpp
class PipelineBuilder {
public:
  // adds Reader as the first handler
  explicit PipelineBuilder(istream& in);

  // adds a new Filter handler
  PipelineBuilder& FilterBy(Filter::Function filter);

  // adds a new Copier handler
  PipelineBuilder& CopyTo(string recipient);

  // adds a new Sender handler
  PipelineBuilder& Send(ostream& out);

  // builds the chain using the Worker::SetNext method
  // and returns the first handler in the constructed chain
  unique_ptr<Worker> Build();
};
```

**Requirements:**

**Worker**
- The `SetNext` method should take ownership of the next handler in the chain.
- The `PassOn` method should call the `Process` method of the next handler if it has been set.

**Reader**
- The constructor should take an input stream (`istream&`), from which emails will be read.
- The `Run` method should read all emails from the input stream and pass each one on. An email is represented in the input stream by the fields `from`, `to`, and `body`, each on its own line.

**Filter**
- The constructor should take a predicate of type `function<bool(const Email&)>`.
- The `Process` method should pass on only the messages that satisfy the predicate.

**Copier**
- The constructor should take a recipient's address as a string.
- The `Process` method should pass the email to both the original recipient and the one specified in the constructor. If they are the same, no duplication is needed.

**Sender**
- The constructor should take a stream to which messages will be written.
- The `Process` method should write messages to the stream in the same format they were read.

All handlers should pass messages down the chain unless explicitly required otherwise.

**PipelineBuilder**
- The constructor should initialize the chain of handlers with a `Reader` handler using the provided input stream.
- Methods with a return type of `PipelineBuilder&` should return a reference to the instance of the class they were called on and add a new handler to the end of the chain (e.g., `Filter` for `FilterBy`, `Sender` for `Send`, etc.).
- The `Build` method should return the complete chain of handlers; once it's completed, the `PipelineBuilder` instance is assumed not to be used again.