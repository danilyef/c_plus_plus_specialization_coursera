#include "test_runner.h"
#include <sstream>
#include <string>
using namespace std;

class Logger {
public:
    explicit Logger(ostream& output_stream) : os(output_stream) {
    }

    void SetLogLine(bool value) { log_line = value; }
    void SetLogFile(bool value) { log_file = value; }
    
    void SetFile(const string& filename) {file = filename;}
    void SetLine(int line_number) {line = line_number;}

    void Log(const string& message){                                                                                                                 
    if (log_file && log_line){                   
        os << file << ":" << line << " ";                  
    } else if (log_file){           
        os << file << " ";                                    
    } else if (log_line){           
        os << "Line" << " " << line << " ";              
    }                                                                            
    
    os << message << "\n";                                                         
                                                                               
                                                           
}


private:
    ostream& os;
    bool log_line = false;
    bool log_file = false;
    string file;
    int line;
};

#define LOG(logger, message) \
  logger.SetFile(__FILE__);  \
  logger.SetLine(__LINE__);  \
  logger.Log(message);




void TestLog() {
/* To write unit tests in this task, we need to fix specific line numbers in the expected value
 * (see the variable 'expected' below). If we add any code above the TestLog function,
 * these line numbers change, and our test starts failing. This is inconvenient.
 *
 * To avoid this, we use a special macro #line
 * (http://en.cppreference.com/w/cpp/preprocessor/line), which allows
 * redefining the line number and file name. Thanks to it, the line numbers
 * inside the TestLog function will be fixed regardless of the code we add before it. */

#line 1 "logger.cpp"

  ostringstream logs;
  Logger l(logs);
  LOG(l, "hello");

  l.SetLogFile(true);
  LOG(l, "hello");

  l.SetLogLine(true);
  LOG(l, "hello");

  l.SetLogFile(false);
  LOG(l, "hello");

  string expected = "hello\n";
  expected += "logger.cpp hello\n";
  expected += "logger.cpp:10 hello\n";
  expected += "Line 13 hello\n";
  ASSERT_EQUAL(logs.str(), expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestLog);
}

