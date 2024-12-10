#include "test_runner.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <utility>
#include <map>
#include <optional>
#include <unordered_set>

using namespace std;




struct HttpRequest {
  string method, path, body;
  map<string, string> get_params;
};

pair<string, string> SplitBy(const string& what, const string& by) {
  size_t pos = what.find(by);
  if (by.size() < what.size() && pos < what.size() - by.size()) {
    return {what.substr(0, pos), what.substr(pos + by.size())};
  } else {
    return {what, {}};
  }
}

template<typename T>
T FromString(const string& s) {
  T x;
  istringstream is(s);
  is >> x;
  return x;
}

pair<size_t, string> ParseIdAndContent(const string& body) {
  auto [id_string, content] = SplitBy(body, " ");
  return {FromString<size_t>(id_string), content};
}

struct LastCommentInfo {
  size_t user_id, consecutive_count;
};


struct HttpHeader {
  string name, value;
};

ostream& operator<<(ostream& output, const HttpHeader& h) {
  return output << h.name << ": " << h.value;
}

bool operator==(const HttpHeader& lhs, const HttpHeader& rhs) {
  return lhs.name == rhs.name && lhs.value == rhs.value;
}

struct ParsedResponse {
  int code;
  vector<HttpHeader> headers;
  string content;
};

//#####################################################################################################

enum class HttpCode {
  Ok = 200,
  NotFound = 404,
  Found = 302,
};

std::string enum_to_string(HttpCode code) {
    switch (code) {
        case HttpCode::Ok:
            return "HTTP/1.1 200 OK";
        case HttpCode::NotFound:
            return "HTTP/1.1 404 Not found";
        case HttpCode::Found:
            return "HTTP/1.1 302 Found";
        default:
            return "Unknown";
    }
}

class HttpResponse {
public:
  explicit HttpResponse(HttpCode code);

  HttpResponse& AddHeader(string name, string value);
  HttpResponse& SetContent(string a_content);
  HttpResponse& SetCode(HttpCode a_code);
  HttpCode GetCode() const;
  const vector<HttpHeader>& GetHeaders() const;
  const string& GetContent() const;

  friend ostream& operator << (ostream& output, const HttpResponse& resp);
private:

  HttpCode code;
  vector<HttpHeader> headers;
  size_t content_length;
  string content;



};

HttpResponse::HttpResponse(HttpCode code) : code(code) {};

HttpResponse& HttpResponse::AddHeader(string name, string value){
  headers.push_back({name,value});
  return *this;
};

HttpResponse& HttpResponse::SetContent(string a_content){
  content_length = a_content.size();
  content = std::move(a_content);
  return *this;
};

HttpResponse& HttpResponse::SetCode(HttpCode a_code){
  code = a_code;
  return *this;
};

HttpCode HttpResponse::GetCode() const {
    return code;
  }

const vector<HttpHeader>& HttpResponse::GetHeaders() const {
  return headers;
}

const string& HttpResponse::GetContent() const {
  return content;
}


ostream& operator << (ostream& output, const HttpResponse& resp){
  const string content_length_header = "Content-Length";
  
  output << enum_to_string(resp.code) << "\n";
  for(const auto& header: resp.headers){
    if (header.name != content_length_header) {
      output << header.name << ": " << header.value << '\n';
    }
  }

  if (resp.GetContent().size() > 0) {
      output << content_length_header << ": " << resp.content_length << '\n';
  }
  output << '\n' << resp.content;
  return output;

};

//#####################################################################################################


class CommentServer {
private:
  vector<vector<string>> comments_;
  std::optional<LastCommentInfo> last_comment;
  unordered_set<size_t> banned_users;

public:
  HttpResponse ServeRequest(const HttpRequest& req){
    HttpResponse response(HttpCode::Ok);
    if (req.method == "POST") {
      if (req.path == "/add_user") {
        comments_.emplace_back();
        auto result = to_string(comments_.size() - 1);
        response.SetContent(result);
      
      } else if (req.path == "/add_comment") {
        auto [user_id, comment] = ParseIdAndContent(req.body);

        if (!last_comment || last_comment->user_id != user_id) {
          last_comment = LastCommentInfo {user_id, 1};
        } else if (++last_comment->consecutive_count > 3) {
          banned_users.insert(user_id);
        }

        if (banned_users.count(user_id) == 0) {
          comments_[user_id].push_back(string(comment));

        } else {
          response.SetCode(HttpCode::Found).AddHeader("Location","/captcha");
        }
      } else if (req.path == "/checkcaptcha") {
        if (auto [id, code] = ParseIdAndContent(req.body); code == "42") {
          banned_users.erase(id);
          if (last_comment && last_comment->user_id == id) {
            last_comment.reset();
          }
        } else{
          response.SetCode(HttpCode::Found).AddHeader("Location","/captcha");
        }
      } else {
        response.SetCode(HttpCode::NotFound);
      }
    } else if (req.method == "GET") {
      if (req.path == "/user_comments") {
        auto user_id = FromString<size_t>(req.get_params.at("user_id"));
        string result;
        for (const string& c : comments_[user_id]) {
          result += c + '\n';
        }
        response.SetContent(result);
      } else if (req.path == "/captcha") {
        response.SetContent("What's the answer for The Ultimate Question of Life, the Universe, and Everything?");
      } else {
        response.SetCode(HttpCode::NotFound);
      }
    }
    return response;
  }
  
};



istream& operator >>(istream& input, ParsedResponse& r) {
  string line;
  getline(input, line);

  {
    istringstream code_input(line);
    string dummy;
    code_input >> dummy >> r.code;
  }

  size_t content_length = 0;

  r.headers.clear();
  while (getline(input, line) && !line.empty()) {
    if (auto [name, value] = SplitBy(line, ": "); name == "Content-Length") {
      istringstream length_input(value);
      length_input >> content_length;
    } else {
      r.headers.push_back( {std::move(name), std::move(value)});
    }
  }

  r.content.resize(content_length);
  input.read(r.content.data(), r.content.size());
  return input;
}

void Test(CommentServer& srv, const HttpRequest& request, const ParsedResponse& expected) {
  stringstream ss;
  HttpResponse resp = srv.ServeRequest(request);

  ASSERT_EQUAL(static_cast<int>(resp.GetCode()), expected.code);
  ASSERT_EQUAL(resp.GetHeaders(), expected.headers);
  ASSERT_EQUAL(resp.GetContent(), expected.content);
}

template <typename CommentServer>
void TestServer() {
  CommentServer cs;

  const ParsedResponse ok{200};
  const ParsedResponse redirect_to_captcha{302, {{"Location", "/captcha"}}, {}};
  const ParsedResponse not_found{404};

  Test(cs, {"POST", "/add_user"}, {200, {}, "0"});
  Test(cs, {"POST", "/add_user"}, {200, {}, "1"});
  Test(cs, {"POST", "/add_comment", "0 Hello"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Hi"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Buy my goods"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Enlarge"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Buy my goods"}, redirect_to_captcha);
  Test(cs, {"POST", "/add_comment", "0 What are you selling?"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Buy my goods"}, redirect_to_captcha);
  Test(
    cs,
    {"GET", "/user_comments", "", {{"user_id", "0"}}},
    {200, {}, "Hello\nWhat are you selling?\n"}
  );
  Test(
    cs,
    {"GET", "/user_comments", "", {{"user_id", "1"}}},
    {200, {}, "Hi\nBuy my goods\nEnlarge\n"}
  );
  Test(
    cs,
    {"GET", "/captcha"},
    {200, {}, {"What's the answer for The Ultimate Question of Life, the Universe, and Everything?"}}
  );
  Test(cs, {"POST", "/checkcaptcha", "1 24"}, redirect_to_captcha);
  Test(cs, {"POST", "/checkcaptcha", "1 42"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Sorry! No spam any more"}, ok);
  
  Test(
    cs,
    {"GET", "/user_comments", "", {{"user_id", "1"}}},
    {200, {}, "Hi\nBuy my goods\nEnlarge\nSorry! No spam any more\n"}
  );

  Test(cs, {"GET", "/user_commntes"}, not_found);
  Test(cs, {"POST", "/add_uesr"}, not_found);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestServer<CommentServer>);
}
