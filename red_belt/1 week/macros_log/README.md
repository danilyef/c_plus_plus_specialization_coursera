#### Programming Assignment "LOG Macro" ####
You are given a Logger class and a LOG macro.

```cpp
class Logger {
public:
  explicit Logger(ostream& output_stream) : os(output_stream) {
  }

  void SetLogLine(bool value) { log_line = value; }
  void SetLogFile(bool value) { log_file = value; }

  void Log(const string& message);

private:
  ostream& os;
  bool log_line = false;
  bool log_file = false;
};

#define LOG(logger, message) ...
```

The parameters of the LOG macro are an object of the Logger class and a string message that should be passed to the Log method. Depending on the settings of the Logger class object, the logged message should be preceded by the file name or line number. Refer to the unit tests in the solution template for a more detailed description of the behavior.

Implement the LOG macro to add the file name and line number to the logged message based on the settings of the logger object. Submit for review a cpp file containing:

- Implementation of the LOG macro
- Declaration of the Logger class, and you can add additional fields and methods as needed
- Definitions for all methods of the Logger class
- log.cpp