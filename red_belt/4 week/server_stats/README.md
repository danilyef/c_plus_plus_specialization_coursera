#### Programming Task: "Web Server Statistics"

Description:
Let's imagine we have a web server that serves requests to an online store. It supports the following set of HTTP requests:

GET / HTTP/1.1 — get the main page of the store

POST /order HTTP/1.1 — place a new order

POST /product HTTP/1.1 — add a new product to the store (admin command)

GET /order HTTP/1.1 — get order details

PUT /product HTTP/1.1 — same as POST /order HTTP/1.1

GET /basket HTTP/1.1 — get the contents of the current client's basket

DELETE /product HTTP/1.1 — delete a product from the online store (admin command)

GET /help HTTP/1.1 — get a page on how to use the online store

From the perspective of the HTTP protocol, the first parts of the requests above ("GET", "POST", "PUT", "DELETE") are called methods. The second parts are called URIs (Uniform Resource Identifier). The third part is the protocol version. Thus, our web server supports 4 methods: GET, POST, PUT, DELETE, and 5 URIs: "/", "/order", "/product", "/basket", "/help".

The main system administrator of our server is concerned about its scalability, and initially, he decided to study the usage statistics. He wants to count for each method and each URI how many times it occurred in requests to the server over the past month. He asked you to help with this.

You already have some codebase for studying requests to the server, and you want to use it to save time. You have a header file http_request.h, which contains the HttpRequest structure:

```cpp
#pragma once

#include <string_view>

using namespace std;

struct HttpRequest {
  string_view method, uri, protocol;
};
```

Additionally, there is a header file stats.h containing declarations of the Stats class and the ParseRequest function:

```cpp
#pragma once

#include "http_request.h"

#include <string_view>
#include <map>

using namespace std;

class Stats {
public:
  void AddMethod(string_view method);
  void AddUri(string_view uri);
  const map<string_view, int>& GetMethodStats() const;
  const map<string_view, int>& GetUriStats() const;
};

HttpRequest ParseRequest(string_view line);
```

Finally, you have a ready-made function ServeRequests:

```cpp
Stats ServeRequests(istream& input) {
  Stats result;
  for (string line; getline(input, line); ) {
    const HttpRequest req = ParseRequest(line);
    result.AddUri(req.uri);
    result.AddMethod(req.method);
  }
  return result;
}
```

Based on the implementation of the ServeRequests function, you need to implement the Stats class and the ParseRequest function. Additional requirements for the Stats class:

- The GetMethodStats method returns a map in which, for each method, it stores how many times it occurred as an argument of the AddMethod method.
- The GetUriStats method works similarly for URIs.
- If the method passed to the AddMethod method is not supported by our server (the list of supported methods is provided above), then the counter for the "UNKNOWN" method should be incremented by one (see unit tests in the solution template for more details).
- If the URI passed to the AddUri method is not supported by our server, then the counter for the "unknown" URI should be incremented by one.

Submit an archive for verification consisting of files stats.h and stats.cpp (as well as any other files you deem necessary to add to your project). Your files should not contain the implementation of the ServeRequests function (if your submission contains the ServeRequests function, you will receive a compilation error).