#include "test_runner.h"
#include <iostream>
#include <vector>

using namespace std;



template <typename T>
class Deque{
public:
    Deque() {};

    bool Empty() const {
        return push_front_deq.empty() &&  push_back_deq.empty();
    };

    size_t Size() const {
        return push_front_deq.size() + push_back_deq.size();
    };

    const T& operator[](size_t index) const {
        if(index >= push_front_deq.size()){
            return push_back_deq[index - push_front_deq.size()];
        } 
        return push_front_deq[push_front_deq.size() - index - 1];
    };

    T& operator[](size_t index) {
        if(index >= push_front_deq.size()){
            return push_back_deq[index - push_front_deq.size()];
        } 
        return push_front_deq[push_front_deq.size() - index - 1];
    };

    void PushFront(T value){
        push_front_deq.push_back(value);
    };

    void PushBack(T value){
        push_back_deq.push_back(value);
    };

    const T& Front() const {
        if(push_front_deq.empty()){
            return push_back_deq.front();
        } else{
            return push_front_deq.back();
        }
        
    };

    T& Front(){
        if(push_front_deq.empty()){
            return push_back_deq.front();
        } else{
            return push_front_deq.back();
        }
        
    };

    const T& Back() const {
        if (push_back_deq.empty()){
            return push_front_deq.front();
        } else{
            return push_back_deq.back();
        }
    };

    T& Back(){
        if (push_back_deq.empty()){
            return push_front_deq.front();
        } else{
            return push_back_deq.back();
        }
    };



    const T& At(size_t index) const {
        if(index >= (push_front_deq.size() + push_back_deq.size())){
            throw std::out_of_range ("index out of range");
        } else if(index >= push_front_deq.size()){
            return push_back_deq.at(index - push_front_deq.size());
        } 
        return push_front_deq.at(push_front_deq.size() - index - 1);
    };
    
    T& At(size_t index){
        if(index >= (push_front_deq.size() + push_back_deq.size())){
            throw std::out_of_range ("index out of range");
        } else if(index >= push_front_deq.size()){
            return push_back_deq.at(index - push_front_deq.size());
        } 
        return push_front_deq.at(push_front_deq.size() - index - 1);

    };



private:

    vector<T> push_front_deq;
    vector<T> push_back_deq;

};

void TestTable() {
    Deque<int> deq;
    ASSERT_EQUAL(deq.Size(), 0);
    ASSERT_EQUAL(deq.Empty(), true);

    deq.PushBack(2);
    deq.PushBack(3);
    deq.PushBack(4);
    deq.PushBack(5);
    ASSERT_EQUAL(deq.Front(), 2);
    ASSERT_EQUAL(deq.Back(), 5);
    ASSERT_EQUAL(deq.Empty(), false);
    ASSERT_EQUAL(deq.Size(), 4);

    ASSERT_EQUAL(deq.At(3), 5); 
    ASSERT_EQUAL(deq.At(1), 3);

    ASSERT_EQUAL(deq[3], 5); 
    ASSERT_EQUAL(deq[1], 3); 

    deq.PushFront(1);
    deq.PushFront(9);
    deq.PushFront(10);
    deq.PushFront(11);
    deq.PushFront(12);
    ASSERT_EQUAL(deq.Front(), 12);
    ASSERT_EQUAL(deq.Back(), 5);
    ASSERT_EQUAL(deq.Empty(), false);
    ASSERT_EQUAL(deq.Size(), 9);

    ASSERT_EQUAL(deq.At(1), 11);
    ASSERT_EQUAL(deq.At(3), 9); 
    ASSERT_EQUAL(deq.At(4), 1);  
    ASSERT_EQUAL(deq.At(5), 2);
    ASSERT_EQUAL(deq.At(8), 5);

    ASSERT_EQUAL(deq[1], 11);
    ASSERT_EQUAL(deq[3], 9); 
    ASSERT_EQUAL(deq[4], 1);  
    ASSERT_EQUAL(deq[5], 2);
    ASSERT_EQUAL(deq[8], 5);

}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
