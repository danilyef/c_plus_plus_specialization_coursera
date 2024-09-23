#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


struct Email {
  string from;
  string to;
  string body;
};


class Worker {
public:
  virtual ~Worker() = default;
  virtual void Process(unique_ptr<Email> email) = 0;
  virtual void Run(){
    throw logic_error("Not implemented");
  };

protected:
  // реализации должны вызывать PassOn, чтобы передать объект дальше
  // по цепочке обработчиков
  
  void PassOn(unique_ptr<Email> email) const{
    if (next_worker) {
      next_worker->Process(std::move(email));
    }
  };
  unique_ptr<Worker> next_worker;

public:

  void SetNext(unique_ptr<Worker> next){
    if (!next_worker){
      next_worker = std::move(next);
    } else{
      Worker* current_worker = next_worker.get();
      while(current_worker->next_worker){
        current_worker = current_worker->next_worker.get();
      }
      current_worker->next_worker = std::move(next);
    }
  }
};


class Reader : public Worker {
public:
  Reader(istream& input_stream) : input_stream(input_stream) {}

 void Run() override {
    while (input_stream) {
        Email email;
        getline(input_stream, email.from);
        if (input_stream.eof()) continue;
        getline(input_stream, email.to);
        if (input_stream.eof()) continue;
        getline(input_stream, email.body);
        if (input_stream.eof()) continue;

        PassOn(make_unique<Email>(std::move(email)));
    }
  }

  void Process(unique_ptr<Email> email) override{
    throw logic_error("Not implemented");
  }

private:
  istream& input_stream;

};


class Filter : public Worker {
public:
  using Function = function<bool(const Email&)>;

  Filter(Function filter) : filter(filter) {} 

  void Process(unique_ptr<Email> email) override{
    if (filter(*email)){
      PassOn(std::move(email));
    }
  }

private:
  Function filter;
};


class Copier : public Worker {
public:

  Copier(string recipient) : recipient(recipient) {}

  void Process(unique_ptr<Email> email) override{
    if (email->to != recipient){
      Email copy = *email;
      PassOn(make_unique<Email>(copy));
    }
    email->to = recipient;
    PassOn(std::move(email));
  }
private:
  string recipient;
};


class Sender : public Worker {
public:
  Sender(ostream& out) : out(out) {}

  void Process(unique_ptr<Email> email) override{
    out << email->from << endl;
    out << email->to << endl;
    out << email->body << endl;
    PassOn(std::move(email));
  }

private:
  ostream& out;
};


// реализуйте класс
class PipelineBuilder {
public:
  // добавляет в качестве первого обработчика Reader
  explicit PipelineBuilder(istream& in) : reader(make_unique<Reader>(in)) {}

  // добавляет новый обработчик Filter
  PipelineBuilder& FilterBy(Filter::Function filter){
    reader->SetNext(make_unique<Filter>(filter));
    return *this;
  }

  // добавляет новый обработчик Copier
  PipelineBuilder& CopyTo(string recipient){
    reader->SetNext(make_unique<Copier>(recipient));
    return *this;
  }

  // добавляет новый обработчик Sender
  PipelineBuilder& Send(ostream& out){
    reader->SetNext(make_unique<Sender>(out));
    return *this;
  }

  // возвращает готовую цепочку обработчиков
  unique_ptr<Worker> Build(){
    return std::move(reader);
  }

private:
  unique_ptr<Reader> reader;
};


void TestSanity() {
  string input = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "ralph@example.com\n"
    "erich@example.com\n"
    "I do not make mistakes of that kind\n"
  );
  istringstream inStream(input);
  ostringstream outStream;

  PipelineBuilder builder(inStream);
  builder.FilterBy([](const Email& email) {
    return email.from == "erich@example.com";
  });
  builder.CopyTo("richard@example.com");
  builder.Send(outStream);
  auto pipeline = builder.Build();

  pipeline->Run();

  string expectedOutput = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "erich@example.com\n"
    "richard@example.com\n"
    "Are you sure you pressed the right button?\n"
  );
  //cout << outStream.str() << endl;
  //cout << "########################" << endl;
  //cout << expectedOutput << endl;
  //cout << "########################" << endl;
  ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSanity);
  return 0;
}
