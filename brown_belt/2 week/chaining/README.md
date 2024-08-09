### Programming Task: "Comment Server

**Foreword**

In this task, we will explore a technique known as chaining, which is widely used in many programming languages, especially in JavaScript. Chaining also has its niche in C++. The `this` pointer is necessary for implementing chaining. Furthermore, to ensure the task does not seem artificial, we will examine the use of this technique in a real practical situation encountered by one of the course instructors.

**Task**

You have joined a team that is developing a web comment server. This server allows you to create new users, post new comments, and read all comments from a selected user. Additionally, the team has recently become concerned with combating spammers. If a user is recognized as a spammer, they are blocked and redirected to a captcha page where they must confirm that they are human. If the captcha is entered successfully, the user is unblocked and can resume posting comments.

A fairly simple algorithm is used to identify spammers—a user is considered a spammer if they post three consecutive comments (see the server implementation in the solution template).

The server operates using the HTTP protocol and processes the following requests:

- `POST /add_user`: Adds a new user and returns a 200 OK response, with the ID of the newly added user in the body (see implementation in the solution template).
- `POST /add_comment`: Extracts the user ID and new comment from the request body. If the user is recognized as a spammer, it returns a 302 Found with a Location header: `/captcha`, redirecting the user to the captcha page; otherwise, it saves the comment and returns 200 OK.
- `GET /user_comments?user_id=[id]`: Returns a 200 OK response, with all comments from the user `id` in the body, separated by newline characters.
- `GET /captcha`: Returns a 200 OK response, with the captcha page in the body (for simplicity in this task, we just return a question for the user to answer; in practice, this could be a full HTML page).
- `POST /checkcaptcha`: Extracts the answer to the captcha question from the request body. If it is correct, the user is unblocked, and a 200 OK response is returned; if not, a 302 Found with a Location header: `/captcha` is returned.

If the request method is not POST or GET, or the request path does not match any of the above, the server responds with 404 Not Found.

The web server is implemented in code using the `CommentServer` class:

```cpp
struct HttpRequest {
  string method, path, body;
  map<string, string> get_params;
};

class CommentServer {
public:
  void ServeRequest(const HttpRequest& req, ostream& response_output);

private:
  ...
};
```

Its `ServeRequest` method takes an HTTP request, processes it, and writes the HTTP response to the output stream `response_output` (this stream can be linked to a network connection). When writing the HTTP response to the output stream, the following format is used:

```
HTTP/1.1 [response code] [comment]
[Header 1]: [Header value 1]
[Header 2]: [Header value 2]
...
[Header N]: [Header value N]
<empty line>
[Response body]
```

- Response code: 200, 302, 404, etc.
- Comment: "Found", "OK", "Not Found", etc.
- Header X: Name of the header, e.g., "Location"
- Response body: For example, the content of the captcha page or the ID of the newly added user. If the response body is not empty, a `Content-Length` header must be present, with a value equal to the length of the response in bytes.

Example of a response to an `/add_user` request, returning a new user ID of 12. `Content-Length` is 2 because "12" is two characters:

```
HTTP/1.1 200 OK
Content-Length: 2

12
```

There is a problem with our server—sometimes it does not respond to requests, and sometimes it returns incorrectly formatted responses. The source of these problems is that responses are manually crafted each time (see solution template). Because of this, we sometimes forget a newline, add an extra one, or make a typo in the response code:

```cpp
void ServeRequest(const HttpRequest& req, ostream& os) {
  if (req.method == "POST") {
    if (req.path == "/add_user") {
      comments_.emplace_back();
      auto response = to_string(comments_.size() - 1);
      os << "HTTP/1.1 200 OK\n" << "Content-Length: " << response.size() << "\n" << "\n"
        << response;
    } else if (req.path == "/checkcaptcha") {
       ...
        os << "HTTP/1.1  20 OK\n\n";
      }
    } else {
      os << "HTTP/1.1 404 Not found\n\n";
    }
  ...
}
```

You decided to solve all problems at once by performing the following refactoring:

- Develop a class `HttpResponse` that will represent an HTTP response; in `operator <<`, you decided to encapsulate the formatting of the HTTP response output to the stream.
- Create a new signature for the `ServeRequest` method—`HttpResponse ServeRequest(const HttpRequest& req)`—which at compile time will ensure that our server always returns at least some response (if we forget to do this, the compiler will issue a warning "control reaches end of non-void function").
- Write the server's response to the output stream in one single place where the `ServeRequest` method is called.

You decided to design the interface of the `HttpResponse` class as follows:

```cpp
enum class HttpCode {
  Ok = 200,
  NotFound = 404,
  Found = 302,
};

class HttpResponse {
public:
  explicit HttpResponse(HttpCode code);

  HttpResponse& AddHeader(string name, string value);
  HttpResponse& SetContent(string a_content);
  HttpResponse& SetCode(HttpCode a_code);

  friend ostream& operator << (ostream& output, const HttpResponse& resp);
};
```

The `AddHeader`, `SetContent`, and `SetCode` methods should return a reference to themselves to allow the response to be formed in one line using chaining: `return HttpResponse(HttpCode::Found).AddHeader("Location", "/captcha");`. The `HttpCode` enumeration passed to the constructor of the `HttpResponse` class ensures that we do not make a mistake in the response code.

This refactoring is what you need to perform in this task. Submit a cpp file that:

- Contains the implementation of the `HttpResponse` class.
- Contains the implementation of the `CommentServer` class with a public method `HttpResponse ServeRequest(const HttpRequest& req)`.

The server should implement the protocol described above.

**Clarifications for implementing the `HttpResponse` class:**

- The `AddHeader`, `SetContent`, and `SetCode` methods should return a reference to the object for which they are called.
- The `AddHeader` method always adds a new header to the response, even if a header with that name already exists.
- `operator<<` for the `HttpResponse` class should output the HTTP response in the format described above in the `ServeRequest` method description; headers can be output in any order. If the HTTP response has non-empty content, exactly one `Content-Length` header must be output, with a value equal to the size of the content in bytes.