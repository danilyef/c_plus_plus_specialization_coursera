#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate(){
    if(!deallocated_.empty()){
        T* ptr = deallocated_.front();
        allocated_.insert(ptr);
        deallocated_.pop(); 
        return ptr;
    }
    T* ptr = new T;
    allocated_.insert(ptr);
    return ptr;
  }
  T* TryAllocate(){
     if(!deallocated_.empty()){
        T* ptr = deallocated_.front();
        allocated_.insert(ptr);
        deallocated_.pop(); 
        return ptr;
    }
    return nullptr;

  };

  void Deallocate(T* object){
    if(!allocated_.count(object)){
        throw invalid_argument("Object not found in allocated set");
    }
    allocated_.erase(object);
    deallocated_.push(object);
  };

  ~ObjectPool(){
    while(!allocated_.empty()){
        delete *allocated_.begin();
        allocated_.erase(allocated_.begin());
    }
    while(!deallocated_.empty()){
        delete deallocated_.front();
        deallocated_.pop();
    }
  };

private:
  set<T*> allocated_;
  queue<T*> deallocated_;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
