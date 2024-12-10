### Programming Task: Working with the time server 

You are given a *string AskTimeServer()* function that knows the following:

• in the course of its work, it accesses a remote server over the network, requesting the current time;
• if the call to the server was successful, the function returns the current time as a string;
• if a network problem occurs while contacting the server, the function throws an exception *system_error*;
• the function may throw other exceptions to report other problems.

Using the *AskTimeServer* function, write a *TimeServer* class with the following interface:
```objectivec
class TimeServer {
public:
  string GetCurrentTime();
private:
  string LastFetchedTime = "00:00:00";
};
```

The *GetCurrentTime* method should behave like this:

• it must call the *AskTimeServer* function, write its result to the *LastFetchedTime* field and return the value of this field;
• if *AskTimeServer* threw a *system_error* exception, the *GetCurrentTime* method should catch it and return the current value of the *LastFetchedTime* field. Thus, we hide network problems from the user by returning the value that was received during the last successful call to the server;
• if *AskTimeServer* threw another exception, the *GetCurrentTime* method must rethrow it, because within the *TimeServer* class we don't know how to handle non-network problems.
