#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <tuple>
#include <algorithm>

using namespace std;

struct Record {
  string id;
  string title;
  string user;
  int timestamp;
  int karma;
};

struct RecordHolder {
  Record record;
  std::multimap<int, const Record*>::iterator it_timestamp;
  std::multimap<int, const Record*>::iterator it_karma;
  std::multimap<string, const Record*>::iterator it_user;
};

// Реализуйте этот класс
class Database {
public:
  bool Put(const Record& record);
  const Record* GetById(const string& id) const;
  bool Erase(const string& id);

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const;

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const;

  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const;

private:
  unordered_map<string, RecordHolder> database_main;
  multimap<int, const Record*> database_timestamp; 
  multimap<int, const Record*> database_karma;
  multimap<string, const Record*> database_user;
};

bool Database::Put(const Record& record) {
  if (database_main.count(record.id) == 1) {
    return false;
  }
  auto it = database_main.emplace(record.id,RecordHolder{record,{},{},{}}).first;
  const Record* ptr = &it->second.record;
  it->second.it_timestamp = database_timestamp.emplace(record.timestamp, ptr);   
  it->second.it_karma = database_karma.emplace(record.karma, ptr);
  it->second.it_user = database_user.emplace(record.user, ptr);
  return true;
}

const Record* Database::GetById(const string& id) const {
  auto it = database_main.find(id);
  if (it == database_main.end()) {
    return nullptr;
  }
  return &it->second.record;
}

bool Database::Erase(const string& id) {
  auto it = database_main.find(id);
  if (it != database_main.end()) {
    database_timestamp.erase(it->second.it_timestamp);
    database_karma.erase(it->second.it_karma);
    database_user.erase(it->second.it_user);
    database_main.erase(it);
    return true;
  }
  return false;
}

template <typename Callback>
void Database::RangeByTimestamp(int low, int high, Callback callback) const {
  auto it = database_timestamp.lower_bound(low);
  while (it != database_timestamp.end() && it->first <= high) {
    if (!callback(*it->second)) {
      break;
    }
    ++it;
  }
}

template <typename Callback>
void Database::RangeByKarma(int low, int high, Callback callback) const {
  auto it = database_karma.lower_bound(low);
  while (it != database_karma.end() && it->first <= high) {
    if (!callback(*it->second)) {
      break;
    }
    ++it;
  }
}

template <typename Callback>
void Database::AllByUser(const string& user, Callback callback) const {
  auto range = database_user.equal_range(user);
  for (auto it = range.first; it != range.second; ++it) {
    if (!callback(*it->second)) {
      break;
    }
  }
}


void TestRangeBoundaries() {
  const int good_karma = 1000;
  const int bad_karma = -10;

  Database db;
  db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
  db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

  int count = 0;
  db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestSameUser() {
  Database db;
  db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
  db.Put({"id2", "Rethink life", "res", 1536107260, 2000});
  db.Put({"id3", "Nice life", "master", 1536107260, 2000});
  db.Erase("id1");
  db.Put({"id4", "Nice life", "master", 1536107260, 2000});

  int count = 0;
  db.AllByUser("master", [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}


void TestReplacement() {
  const string final_body = "Feeling sad";

  Database db;
  db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
  db.Erase("id");
  db.Put({"id", final_body, "not-master", 1536107260, -10});

  auto record = db.GetById("id");
  ASSERT(record != nullptr);
  ASSERT_EQUAL(final_body, record->title);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestRangeBoundaries);
  RUN_TEST(tr, TestSameUser);
  RUN_TEST(tr, TestReplacement);
  return 0;
}
