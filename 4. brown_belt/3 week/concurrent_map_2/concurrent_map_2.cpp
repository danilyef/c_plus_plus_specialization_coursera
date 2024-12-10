#include "test_runner.h"
#include "profile.h"

#include <future>
#include <mutex>
#include <unordered_map>
#include <vector>
#include <utility>
#include <algorithm>
#include <random>
using namespace std;

template <typename K, typename V, typename Hash = std::hash<K>>
class ConcurrentMap {
public:
  using MapType = std::unordered_map<K, V, Hash>;

  struct WriteAccess {
    std::lock_guard<std::mutex> guard;
    V& ref_to_value;
  };

  struct ReadAccess {
    std::lock_guard<std::mutex> guard;
    const V& ref_to_value;
  };

  struct Bucket {
    MapType thread;
    mutable std::mutex mtx;
  };

  Bucket& GetBucket(const K& key) {
    return buckets[hasher(key) % buckets.size()];
  }

  const Bucket& GetBucket(const K& key) const {
    return buckets[hasher(key) % buckets.size()];
  }

  explicit ConcurrentMap(std::size_t bucket_count): buckets(bucket_count) {};

 
  WriteAccess operator[](const K& key) {
    Bucket& bucket = GetBucket(key);
    return {std::lock_guard(bucket.mtx),bucket.thread[key]};
  };


  ReadAccess At(const K& key) const{
    const Bucket& bucket = GetBucket(key);
    return {std::lock_guard(bucket.mtx),bucket.thread.at(key)};
  };


  bool Has(const K& key) const{
    return GetBucket(key).thread.count(key);
  };

  MapType BuildOrdinaryMap() const{
    MapType result;
    for (const auto& bucket : buckets){
      std::lock_guard<std::mutex> guard(bucket.mtx);
      result.insert(bucket.thread.begin(), bucket.thread.end());
    }
    return result;
  };

private:
  Hash hasher;
  std::vector<Bucket> buckets;
};



//################################################################################

void RunConcurrentUpdates(
    ConcurrentMap<int, int>& cm, std::size_t thread_count, int key_count
) {
  auto kernel = [&cm, key_count](int seed) {
    std::vector<int> updates(key_count);
    std::iota(std::begin(updates), std::end(updates), -key_count / 2);
    std::shuffle(std::begin(updates), std::end(updates), std::default_random_engine(seed));

    for (int i = 0; i < 2; ++i) {
      for (auto key : updates) {
        cm[key].ref_to_value++;
      }
    }
  };

  std::vector<std::future<void>> futures;
  for (std::size_t i = 0; i < thread_count; ++i) {
    futures.push_back(std::async(kernel, i));
  }
}

void TestConcurrentUpdate() {
  const std::size_t thread_count = 3;
  const std::size_t key_count = 50000;

  ConcurrentMap<int, int> cm(thread_count);
  RunConcurrentUpdates(cm, thread_count, key_count);
  const auto result = std::as_const(cm).BuildOrdinaryMap();
  ASSERT_EQUAL(result.size(), key_count);
  for (auto& [k, v] : result) {
    AssertEqual(v, 6, "Key = " + std::to_string(k));
  }
}

void TestReadAndWrite() {
  ConcurrentMap<std::size_t, std::string> cm(5);

  auto updater = [&cm] {
    for (std::size_t i = 0; i < 50000; ++i) {
      cm[i].ref_to_value += 'a';
    }
  };
  auto reader = [&cm] {
    std::vector<std::string> result(50000);
    for (std::size_t i = 0; i < result.size(); ++i) {
      result[i] = cm[i].ref_to_value;
    }
    return result;
  };

  auto u1 = std::async(updater);
  auto r1 = std::async(reader);
  auto u2 = std::async(updater);
  auto r2 = std::async(reader);

  u1.get();
  u2.get();

  for (auto f : {&r1, &r2}) {
    auto result = f->get();
    ASSERT(std::all_of(result.begin(), result.end(), [](const std::string& s) {
      return s.empty() || s == "a" || s == "aa";
    }));
  }
}

void TestSpeedup() {
  {
    ConcurrentMap<int, int> single_lock(1);
    LOG_DURATION("Single lock");
    RunConcurrentUpdates(single_lock, 4, 50000);
  }
  {
    ConcurrentMap<int, int> many_locks(100);
    LOG_DURATION("100 locks");
    RunConcurrentUpdates(many_locks, 4, 50000);
  }
}

void TestConstAccess() {
  const std::unordered_map<int, std::string> expected = {
    {1, "one"},
    {2, "two"},
    {3, "three"},
    {31, "thirty one"},
    {127, "one hundred and twenty seven"},
    {1598, "fifteen hundred and ninety eight"}
  };

  const ConcurrentMap<int, std::string> cm = [&expected] {
    ConcurrentMap<int, std::string> result(3);
    for (const auto& [k, v] : expected) {
      result[k].ref_to_value = v;
    }
    return result;
  }();

  std::vector<std::future<std::string>> futures;
  for (int i = 0; i < 10; ++i) {
    futures.push_back(std::async([&cm, i] {
      try {
        return cm.At(i).ref_to_value;
      } catch (std::exception&) {
        return std::string();
      }
    }));
  }
  futures.clear();

  ASSERT_EQUAL(cm.BuildOrdinaryMap(), expected);
}

void TestStringKeys() {
  const std::unordered_map<std::string, std::string> expected = {
    {"one", "ONE"},
    {"two", "TWO"},
    {"three", "THREE"},
    {"thirty one", "THIRTY ONE"},
  };

  const ConcurrentMap<std::string, std::string> cm = [&expected] {
    ConcurrentMap<std::string, std::string> result(2);
    for (const auto& [k, v] : expected) {
      result[k].ref_to_value = v;
    }
    return result;
  }();

  ASSERT_EQUAL(cm.BuildOrdinaryMap(), expected);
}

struct Point {
  int x, y;
};

struct PointHash {
  std::size_t operator()(Point p) const {
    std::hash<int> h;
    return h(p.x) * 3571 + h(p.y);
  }
};

bool operator==(Point lhs, Point rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

void TestUserType() {
  ConcurrentMap<Point, std::size_t, PointHash> point_weight(5);

  std::vector<std::future<void>> futures;
  for (int i = 0; i < 1000; ++i) {
    futures.push_back(std::async([&point_weight, i] {
      point_weight[Point{i, i}].ref_to_value = i;
    }));
  }

  futures.clear();

  for (int i = 0; i < 1000; ++i) {
    ASSERT_EQUAL(point_weight.At(Point{i, i}).ref_to_value, i);
  }

  const auto weights = point_weight.BuildOrdinaryMap();
  for (int i = 0; i < 1000; ++i) {
    ASSERT_EQUAL(weights.at(Point{i, i}), i);
  }
}

void TestHas() {
  ConcurrentMap<int, int> cm(2);
  cm[1].ref_to_value = 100;
  cm[2].ref_to_value = 200;

  const auto& const_map = std::as_const(cm);
  ASSERT(const_map.Has(1));
  ASSERT(const_map.Has(2));
  ASSERT(!const_map.Has(3));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestConcurrentUpdate);
  RUN_TEST(tr, TestReadAndWrite);
  RUN_TEST(tr, TestSpeedup);
  RUN_TEST(tr, TestConstAccess);
  RUN_TEST(tr, TestStringKeys);
  RUN_TEST(tr, TestUserType);
  RUN_TEST(tr, TestHas);
}
