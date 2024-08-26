#include "test_runner.h"

#include <functional>
#include <string>
#include <optional>
using namespace std;

template <typename T>
class LazyValue {
public:
  explicit LazyValue(std::function<T()> init);

  bool HasValue() const;
  const T& Get() const;

private:
  std::function<T()> init_;
  mutable std::optional<T> value_;
  mutable bool has_value_;
};

template <typename T>
LazyValue<T>::LazyValue(std::function<T()> init) : init_(std::move(init)), has_value_(false) {}




template <typename T>
const T& LazyValue<T>::Get() const {
  if (!has_value_) {
    value_ = init_();
    has_value_ = true;
  }
    return value_.value();
}

template <typename T>
bool LazyValue<T>::HasValue() const {
  return has_value_;
}

void UseExample() {
  const string big_string = "Giant amounts of memory";

  LazyValue<string> lazy_string([&big_string] { return big_string; });

  ASSERT(!lazy_string.HasValue());
  ASSERT_EQUAL(lazy_string.Get(), big_string);
  ASSERT_EQUAL(lazy_string.Get(), big_string);
}

void TestInitializerIsntCalled() {
  bool called = false;

  {
    LazyValue<int> lazy_int([&called] {
      called = true;
      return 0;
    });
  }
  ASSERT(!called);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, UseExample);
  RUN_TEST(tr, TestInitializerIsntCalled);
  return 0;
}
